/**************************************************************************
*
* Copyright (c) 2017-2021, luotang.me <wypx520@gmail.com>, China.
* All rights reserved.
*
* Distributed under the terms of the GNU General Public License v2.
*
* This software is provided 'as is' with no explicit or implied warranties
* in respect of its properties, including, but not limited to, correctness
* and/or fitness for purpose.
*
**************************************************************************/
#include <base/Os.h>
#include <base/Affinity.h>
#include <base/Logger.h>

#include <algorithm>
#include <numaif.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <thread>
#include <fstream>
#include <execinfo.h>
#include <cxxabi.h>

using namespace MSF::BASE;

namespace MSF {
namespace BASE {

OsInfo::OsInfo()
{
    osInit();
}
OsInfo::~OsInfo()
{

}

uint32_t OsInfo::getSuggestThreadNum()
{
    uint32_t n = std::thread::hardware_concurrency();
    MSF_DEBUG << n << " concurrent threads are supported.";
    return n;
}

bool OsInfo::setUser(uid_t user, const std::string & userName)
{
    char *group = NULL;
    struct passwd    *pwd = NULL;
    struct group     *grp = NULL;

     if (user != (uid_t) MSF_CONF_UNSET_UINT) {
         MSF_DEBUG << "User is duplicate.";
         return true;
    }

    if (geteuid() == 0) {
        gid_t groupId;
        if (setgid(groupId) == -1) {
            /* fatal */
            exit(2);
        }

        if (initgroups(userName.c_str(), groupId) == -1) {
            exit(2);
        }

        if (setuid(user) == -1) {
            /* fatal */
            exit(2);
        }

        ////
        pwd = getpwnam(userName.c_str());
        if (pwd == nullptr) {
            return false;
        }

        uid_t user1 = pwd->pw_uid;

        grp = getgrnam(group);
        if (grp == nullptr) {
            return false;
        }
        gid_t group1 = grp->gr_gid;
        return true;
    } else {
        MSF_DEBUG << 
           "The \"user\" directive makes sense only "
           "if the master process runs "
           "with super-user privileges, ignored.";
        return true;
    }
}

//https://blog.csdn.net/zhjutao/article/details/8652252
//https://www.cnblogs.com/cl1024cl/p/6205119.html
/* we don't want our active sessions to be paged out... */
bool OsInfo::disablePageOut()
{
    if (mlockall(MCL_CURRENT | MCL_FUTURE)) {
        MSF_ERROR << "failed to mlockall, diable page out.";
        return false;
    }
    return true;
}

/* oom-killer will not kill us at the night... */
bool OsInfo::oomAdjust()
{
    int fd;
    char path[48];
    struct stat statb;

    errno = 0;
    if (nice(-10) == -1 && errno != 0) {
        MSF_ERROR << "Could not increase process priority:" << strerror(errno);
        return false;
    }

    snprintf(path, 48, "/proc/%d/oom_score_adj", getpid());
    if (stat(path, &statb)) {
        /* older kernel so use old oom_adj file */
        snprintf(path, 48, "/proc/%d/oom_adj", getpid());
    }
    fd = open(path, O_WRONLY);
    if (fd < 0) {
        return false;
    }
    if (write(fd, "-16", 3) < 0) {
        /* for 2.6.11 */
        MSF_ERROR << "Could not set oom score to -16: " <<
                strerror(errno);
    }
    if (write(fd, "-17", 3) < 0) {
        /* for Andrea's patch */
        MSF_ERROR << "Could not set oom score to -17: " <<
                strerror(errno);
    }
    close(fd);
    return true;
}

uint32_t OsInfo::getMaxOpenFds()
{
    uint32_t maxFds = 0;
    struct rlimit rl;
    /* But if possible, get the actual highest FD we can possibly ever see. */
    if (0 == getrlimit(RLIMIT_NOFILE, &rl)) {
        maxFds = rl.rlim_max;
    } else {
        MSF_ERROR << "Failed to query maximum file descriptor; "
                        "falling back to maxconns.";
    }
    return maxFds;
}

bool OsInfo::setMaxOpenFds(const uint64_t maxOpenFds)
{
    /* We're unlikely to see an FD much higher than maxconns. */
    int nextFd = dup(1);
    uint32_t headRoom = 10;      /* account for extra unexpected open FDs */
    struct rlimit rl;

    uint64_t maxFds = maxOpenFds + headRoom + nextFd;

    struct rlimit rlmt;
    rlmt.rlim_cur = (rlim_t)maxFds;
    rlmt.rlim_max = (rlim_t)maxFds;

    /* next_fd used to count */
    close(nextFd);

    //RLIMIT_NOFILE指定此进程可打开的最大文件描述词大一的值,超出此值,将会产生EMFILE错误。
    if (setrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
        MSF_ERROR << "Set rlimit nofile faild, errno: " << errno;
        return false;
    }
    return true;
}

/* allow coredump after setuid() in Linux 2.4.x */
bool OsInfo::enableCoreDump()
{
    #if HAVE_PRCTL && defined(PR_SET_DUMPABLE)
    /* Set Linux DUMPABLE flag */
    if (prctl(PR_SET_DUMPABLE, 1, 0, 0, 0) != 0) {
        MSF_ERROR << "prctl: " << strerror(errno);
        return false;
    }
    #endif

    /* Make sure coredumps are not limited */
    struct rlimit rlim;
    if (getrlimit(RLIMIT_CORE, &rlim) == 0) {
        MSF_INFO << "Coredump curr: " << rlim.rlim_cur 
                << " max is: " << rlim.rlim_max;
        rlim.rlim_cur = rlim.rlim_max;
        if (setrlimit(RLIMIT_CORE, &rlim) == 0) {
            MSF_ERROR << "Enable coredump sucessfully";
            return true;
        }
    }
    MSF_ERROR << "Enable coredump faild:" << strerror(errno);
    return false;
}

//https://blog.csdn.net/u011417820/article/details/71435031
//https://blog.csdn.net/cp3alai/article/details/93968796
//https://blog.csdn.net/fengxinze/article/details/6800175
/**
 * ulimit - c 1024
 * */
bool OsInfo::setCoreDumpSize(const uint64_t maxCoreSize)
{
    if (maxCoreSize == 0) {
        return false;
    }
    struct rlimit rlmt;
    rlmt.rlim_cur = (rlim_t) maxCoreSize;
    rlmt.rlim_max = (rlim_t) maxCoreSize;
    //修改工作进程的core文件尺寸的最大值限制(RLIMIT_CORE),用于在不重启主进程的情况下增大该限制
    if (setrlimit(RLIMIT_CORE, &rlmt) == -1) {
        MSF_ERROR << "Set rlimit core faild, errno: " << errno;
        return false;
    }
    return true;
}

/**
 * 1. echo "1" > /proc/sys/kernel/core_uses_pid
 * 2. sysctl -w kernel.core_uses_pid=1 kernel.core_uses_pid = 1
 * */
bool OsInfo::setCoreUsePid()
{
     std::string pattern = "echo \"1\" > /proc/sys/kernel/core_uses_pid";
     return true;
}

/**
 * 1. echo "/home/core/core-%h-%s-%e-%p-%t" > /proc/sys/kernel/core_pattern
 * 2. sysctl -w kernel.core_pattern=/home/core/core.%h.%s.%e.%p.%s.%t
 * 以下是参数列表:
 * %p - insert pid into filename 添加pid(进程id)
 * %u - insert current uid into filename 添加当前uid(用户id)
 * %g - insert current gid into filename 添加当前gid(用户组id)
 * %s - insert signal that caused the coredump into the filename 添加导致产生core的信号
 * %t - insert UNIX time that the coredump occurred into filename 添加core文件生成时的unix时间
 * %h - insert hostname where the coredump happened into filename 添加主机名
 * %e - insert coredumping executable name into filename 添加导致产生core的命令名
 * */
bool OsInfo::setCorePath(const std::string & path)
{
    std::string cmdCorePath = 
    "echo \"/home/core/core-%h-%s-%e-%p-%t\" > /proc/sys/kernel/core_pattern";
    system(cmdCorePath.c_str());
    return true;
}

/* Display a buffer into a HEXA formated output */
void OsInfo::dumpBuffer(const char *buff, size_t count, FILE* fp)
{
    size_t i, j, c;
    bool printnext = true;

    if (count % 16)
        c = count + (16 - count % 16);
    else
        c = count;

    for (i = 0; i < c; i++) {
        if (printnext) {
            printnext = false;
            fprintf(fp, "%.4zu ", i & 0xffff);
        }
        if (i < count)
            fprintf(fp, "%3.2x", buff[i] & 0xff);
        else
            fprintf(fp, "   ");

        if (!((i + 1) % 8)) {
            if ((i + 1) % 16) {
                fprintf(fp, " -");
            } else {
                fprintf(fp, "   ");
                for (j = i - 15; j <= i; j++) {
                    if (j < count) {
                        if ((buff[j] & 0xff) >= 0x20 && 
                            (buff[j] & 0xff) <= 0x7e) {
                                fprintf(fp, "%c", buff[j] & 0xff);
                            } else {
                                fprintf(fp, ".");
                            }
                    } else {
                        fprintf(fp, " ");
                    }
                }
                fprintf(fp, "\n");
                printnext = true;
            }
        }
    }
}

//https://www.cnblogs.com/mickole/p/3246702.html
void OsInfo::writeStackTrace(const std::string & filePath)
{
    int fd = open(filePath.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);
    void *buffer[100];
    int nptrs;

    nptrs = backtrace(buffer, 100);
    backtrace_symbols_fd(buffer, nptrs, fd);
    if (write(fd, "\n", 1) != 1) {
        /* We don't care, but this stops a warning on Ubuntu */
    }
    close(fd);
}

const std::string OsInfo::stackTrace(bool demangle)
{
    std::string stack;
    const int max_frames = 200;
    void* frame[max_frames];
    int nptrs = ::backtrace(frame, max_frames);
    char** strings = ::backtrace_symbols(frame, nptrs);
    if (strings)
    {
        size_t len = 256;
        char* demangled = demangle ? static_cast<char*>(::malloc(len)) : nullptr;
        for (int i = 1; i < nptrs; ++i)  // skipping the 0-th, which is this function
        {
            if (demangle)
            {
                // https://www.cnblogs.com/BloodAndBone/p/7912179.html 
                // https://panthema.net/2008/0901-stacktrace-demangled/
                // bin/exception_test(_ZN3Bar4testEv+0x79) [0x401909]
                char* left_par = nullptr;
                char* plus = nullptr;
                for (char* p = strings[i]; *p; ++p)
                {
                    if (*p == '(')
                    left_par = p;
                    else if (*p == '+')
                    plus = p;
                }

                if (left_par && plus)
                {
                    *plus = '\0';
                    int status = 0;
                    char* ret = abi::__cxa_demangle(left_par+1, demangled, &len, &status);
                    *plus = '+';
                    if (status == 0)
                    {
                        demangled = ret;  // ret could be realloc()
                        stack.append(strings[i], left_par+1);
                        stack.append(demangled);
                        stack.append(plus);
                        stack.push_back('\n');
                        continue;
                    }
                }
            }
            // Fallback to mangled names
            stack.append(strings[i]);
            stack.push_back('\n');
        }
        free(demangled);
        free(strings);
    }
    return stack;
}


/* Numa Info*/
void OsInfo::vnodeInit(void)
{
#if 0
    int rc;

     en_numa = numa_available();
    if ( en_numa < 0) {
        MSF_ERROR << "Your system does not support NUMA API.";
        return;
    }

     numacnt = numa_max_node();

    MSF_ERROR << "System numa en:" <<  en_numa;
    MSF_ERROR << "System numa num:" <<  numacnt;

    int nd;
    char *man = (char *)numa_alloc(1000);
    *man = 1;
    if (get_mempolicy(&nd, NULL, 0, man, MPOL_F_NODE|MPOL_F_ADDR) < 0)
        perror("get_mempolicy");
    else
        MSF_ERROR << "my node is : " << nd;

    numa_free(man, 1000);
#endif
}

bool OsInfo::sysInit()
{
    struct rlimit rlmt;
    struct utsname u;

    if (uname(&u) == -1) {
        MSF_ERROR << "Uname failed, errno:" << errno;
        return false;
    }

    sysName_ = u.sysname;
    nodeName_ = u.nodename;
    release_ = u.release;
    version_ = u.version;
    machine_ = u.machine;
    domainName_ = u.domainname;

    /* GNU fuction 
    * getpagesize(); numa_pagesize()
    * get_nprocs_conf();
    * get_nprocs();
    */
    pageSize_ = sysconf(_SC_PAGESIZE);
    pageNumAll_ = sysconf(_SC_PHYS_PAGES);
    pageNumAva_ = sysconf(_SC_AVPHYS_PAGES);
    memSize_ = pageSize_ * pageNumAll_ / MB;

    /* Gather number of processors and CPU ticks linux2.6 Later
     refer:http://blog.csdn.net/u012317833/article/details/39476831 */
    #ifdef WIN32
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    cpuConf_ = si.dwNumberOfProcessors;
    #else
    cpuConf_ = sysconf(_SC_NPROCESSORS_CONF);
    #endif

    #ifdef WIN32
    SYSTEM_INFO info; 
    GetSystemInfo(&info); 
    cpuOnline_ = info.dwNumberOfProcessors;
    #else
    cpuOnline_ = sysconf(_SC_NPROCESSORS_ONLN);
    #endif
    maxFileFds_ = sysconf(_SC_OPEN_MAX);
    tickSpersec_ = sysconf(_SC_CLK_TCK);
    maxHostName_ = sysconf(_SC_HOST_NAME_MAX);
    maxLoginName_ = sysconf(_SC_LOGIN_NAME_MAX);

    if (getrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
        MSF_ERROR << "Getrlimit failed, errno:" << errno;
        return false;
    }

    maxSocket_ = (int)rlmt.rlim_cur;
    return true;
}

bool OsInfo::getMemUsage()
{
    std::string pidStatusPath = "/proc/" + std::to_string(getpid()) + "/status";
    std::ifstream fin(pidStatusPath);  
    if (!fin) 
    {   
        MSF_ERROR << "Error opening " << pidStatusPath << " for input";
        return false;  
    }

    std::string line;  
    while (getline(fin, line)) {  
        MSF_INFO << "Read from file: " << line;
        //kb
        if (line.find("VmSize")) {

        } else if (line.find("VmRSS")) {

        }
    }
}

bool OsInfo::getHddUsage()
{
    FILE *fp = NULL;
    char buffer[80],a[80],d[80],e[80],f[80], buf[256];
    double c,b;
    double dev_total = 0, dev_used = 0;

    fp = popen("df", "r");
    if (!fp) {
        return false;
    }

    fgets(buf, sizeof(buf), fp);
    while (6 == fscanf(fp, "%s %lf %lf %s %s %s",
        a, &b, &c, d, e, f)) {
        dev_total += b;
        dev_used += c;
    }

    struct HddInfo hdd;
    hdd.total = dev_total / MB;
    hdd.used_rate = dev_used / dev_total * 100;
    pclose(fp);
    return true;
}

bool OsInfo::getMemInfo(struct MemInfo & mem)
{  
    //https://www.cnblogs.com/JCSU/articles/1190685.html
    std::ifstream fin("/proc/meminfo");  
    if (!fin) 
    {   
        MSF_ERROR << "Error opening /proc/meminfo for input";   
        return false;  
    }

    std::string line;  
    while (getline(fin, line)) {  
        MSF_INFO << "Read from file: " << line;
        if (line.find("MemTotal")) {

        } else if (line.find("MemFree")) {

        } else if (line.find("MemAvailable")) {

        } else if (line.find("Shmem")) {

        } else if (line.find("Slab")) {

        } else if (line.find("HugePages_Total")) {

        } else if (line.find("HugePages_Free")) {

        } else if (line.find("HugePages_Rsvd")) {

        } else if (line.find("HugePages_Surp")) {

        } else if (line.find("Hugepagesize")) {

        } else if (line.find("DirectMap4k")) {

        } else if (line.find("DirectMap2M")) {

        } else if (line.find("DirectMap1G")) {

        }
    }
    return true;
}

void OsInfo::cpuId(uint32_t i, uint32_t *buf)
{
#if (( __i386__ || __amd64__ ) && ( __GNUC__ || __INTEL_COMPILER ))
#if ( __i386__ )
    /*
     * we could not use %ebx as output parameter if gcc builds PIC,
     * and we could not save %ebx on stack, because %esp is used,
     * when the -fomit-frame-pointer optimization is specified.
     */
    __asm__ (
    "    mov    %%ebx, %%esi;  "

    "    cpuid;                "
    "    mov    %%eax, (%1);   "
    "    mov    %%ebx, 4(%1);  "
    "    mov    %%edx, 8(%1);  "
    "    mov    %%ecx, 12(%1); "

    "    mov    %%esi, %%ebx;  "

    : : "a" (i), "D" (buf) : "ecx", "edx", "esi", "memory" );
#else /* __amd64__ */
    uint32_t  eax, ebx, ecx, edx;

    __asm__ ("cpuid" : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx) : "a" (i) );

    buf[0] = eax;
    buf[1] = ebx;
    buf[2] = edx;
    buf[3] = ecx;
#endif
#endif
}

/* auto detect the L2 cache line size of modern and widespread CPUs
 * 这个函数便是在获取CPU的信息,根据CPU的型号对ngx_cacheline_size进行设置*/
void OsInfo::cpuInit()
{
#if (( __i386__ || __amd64__ ) && ( __GNUC__ || __INTEL_COMPILER ))
    char  *vendor;
    uint32_t vbuf[5], cpu[4], model;

    memset(vbuf, 0, sizeof(vbuf));

    cpuId(0, vbuf);

    vendor = (char *) &vbuf[1];

    if (vbuf[0] == 0) {
        MSF_ERROR <<"Get cpu info failed.";
        return;
    }

    cpuId(1, cpu);

    if (strcmp(vendor, "GenuineIntel") == 0) {
        switch ((cpu[0] & 0xf00) >> 8) {
            /* Pentium */
            case 5:
                MSF_DEBUG << "This cpu is Pentium.";
                cacheLineSize_ = 32;
                break;
            /* Pentium Pro, II, III */
            case 6:
                MSF_DEBUG << "This cpu is Pentium Pro.";
                cacheLineSize_ = 32;

                model = ((cpu[0] & 0xf0000) >> 8) | (cpu[0] & 0xf0);
                if (model >= 0xd0) {
                    /* Intel Core, Core 2, Atom */
                    cacheLineSize_ = 64;
                }
                break;
            /*
             * Pentium 4, although its cache line size is 64 bytes,
             * it prefetches up to two cache lines during memory read
             */
            case 15:
                MSF_DEBUG << "This cpu is Pentium 4.";
                cacheLineSize_ = 128;
                break;
            default:
                MSF_DEBUG << "This cpu is Default.";
                cacheLineSize_ = 32;
                break;
        }

    } else if (strcmp(vendor, "AuthenticAMD") == 0) {
        MSF_DEBUG << "This cpu is AMD.";
        cacheLineSize_ = 64;
    }
#else
    cacheLineSize_ = 32;
#endif
}

int64_t OsInfo::GetCurCpuTime() 
{
    char file_name[64] = { 0 };
    snprintf(file_name, sizeof(file_name), "/proc/%d/stat", getpid());
    
    FILE* pid_stat = fopen(file_name, "r");
    if (!pid_stat) {
        return -1;
    }

    PidStat result;
    int ret = fscanf(pid_stat, "%ld %s %c %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",
        &result.pid, result.comm, &result.state, &result.ppid, &result.pgrp, &result.session,
        &result.tty_nr, &result.tpgid, &result.flags, &result.minflt, &result.cminflt,
        &result.majflt, &result.cmajflt, &result.utime, &result.stime, &result.cutime, &result.cstime);

    fclose(pid_stat);

    if (ret <= 0) {
        return -1;
    }

    return result.utime + result.stime + result.cutime + result.cstime;
}

int64_t OsInfo::GetTotalCpuTime()
{
    char file_name[] = "/proc/stat";
    FILE* stat = fopen(file_name, "r");
    if (!stat) {
        return -1;
    }

    CpuStat result;
    int ret = fscanf(stat, "%s %ld %ld %ld %ld %ld %ld %ld",
        result.cpu_label, &result.user, &result.nice, &result.system, &result.idle,
        &result.iowait, &result.irq, &result.softirq);

    fclose(stat);

    if (ret <= 0) {
        return -1;
    }

    return result.user + result.nice + result.system + result.idle +
        result.iowait + result.irq + result.softirq;
}


float OsInfo::CalculateCurCpuUseage(int64_t cur_cpu_time_start, int64_t cur_cpu_time_stop,
    int64_t total_cpu_time_start, int64_t total_cpu_time_stop) 
{
    int64_t cpu_result = total_cpu_time_stop - total_cpu_time_start;
    if (cpu_result <= 0) {
        return 0;
    }
    return (cpuOnline_ * 100.0f *(cur_cpu_time_stop - cur_cpu_time_start)) / cpu_result;
}


void OsInfo::dbgOsInfo()
{
    MSF_DEBUG << "OS type:"              <<  sysName_;
    MSF_DEBUG << "OS nodename:"          <<  nodeName_;
    MSF_DEBUG << "OS release:"           <<  release_;
    MSF_DEBUG << "OS version:"           <<  version_;
    MSF_DEBUG << "OS machine:"           <<  machine_;
    MSF_DEBUG << "OS domainname:"        <<  domainName_;
    MSF_DEBUG << "Processors conf:"      <<  cpuConf_;
    MSF_DEBUG << "Processors avai:"      <<  cpuOnline_;
    MSF_DEBUG << "Cacheline size: "      <<  cacheLineSize_;
    MSF_DEBUG << "Pagesize: "            <<  pageSize_;
    MSF_DEBUG << "Pages all num:"        <<  pageNumAll_;
    MSF_DEBUG << "Pages available: "     <<  pageNumAva_;
    MSF_DEBUG << "Memory size:  "        <<  memSize_ << "MB";
    MSF_DEBUG << "Files max opened: "    <<  maxFileFds_;
    MSF_DEBUG << "Socket max opened: "   <<  maxSocket_;
    MSF_DEBUG << "Ticks per second: "    <<  tickSpersec_;
    MSF_DEBUG << "Maxlen host name: "    <<  maxHostName_;
    MSF_DEBUG << "Maxlen login name: "   <<  maxLoginName_;

    MSF_DEBUG << "Memory name1: "        <<  mem_.name1;
    MSF_DEBUG << "Memory total: "        <<  mem_.total;
    MSF_DEBUG << "Memory name2: "        <<  mem_.name2;
    MSF_DEBUG << "Memory free: "         <<  mem_.free;
    MSF_DEBUG << "Memory used rate: "    <<  mem_.used_rate;

    MSF_DEBUG << "Hdd total: "           <<  hdd_.total;
    MSF_DEBUG << "Hdd used_rate: "       <<  hdd_.used_rate;
}

bool OsInfo::osInit()
{
    sysInit();
    vnodeInit();
    dbgOsInfo();
    return true;
}

} /**************************** end namespace BASE ****************************/
} /**************************** end namespace MSF  ****************************/