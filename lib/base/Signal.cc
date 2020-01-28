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
#include <base/Signal.h>
#include <base/Logger.h>
#include <base/Os.h>

namespace MSF {
namespace BASE {

void SignalHandler(int signo)
{
    OsInfo os;
    //如果是日志进程的话，需要刷新buff到文件或者屏幕
    switch (signo) {
        case SIGBUS:
            MSF_ERROR<< "Got sigbus error.";
            raise(SIGKILL);
            break;
         case SIGSEGV:
            MSF_ERROR<< "Got sigsegv error.";
            break;
          case SIGILL:
            MSF_ERROR<< "Got sigill error.";
            break;
          case SIGCHLD:
          default:
            MSF_ERROR<< "Got sigill: " << signo;
            break;
    }
    os.writeStackTrace("trace.log");
    exit(1);
}

void RegSigHandler(int sig, SigHandler handler)
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    /* 安装信号的时候, 设置 SA_RESTART属性, 
    * 那么当信号处理函数返回后, 被该信号中断的系统调用将自动恢复*/
    action.sa_flags =  SA_NODEFER | SA_RESTART;
    sigaction(sig, &action, nullptr);
}

void InitSigHandler()
{
    RegSigHandler(SIGINT,  SignalHandler);//当按下ctrl+c时，它的效果就是发送SIGINT信号
    RegSigHandler(SIGPIPE, SIG_IGN);
    RegSigHandler(SIGHUP,  SIG_IGN);
    RegSigHandler(SIGTERM, SIG_IGN);//kill pid
    RegSigHandler(SIGPIPE, SIG_IGN);
    RegSigHandler(SIGQUIT, SIG_IGN);//ctrl+\代表退出SIGQUIT

     /* 
      * #define    SIGTERM        15
      * #define    SIGKILL        9
      * kill和kill -9, 两个命令在linux中都有杀死进程的效果
      * 然而两命令的执行过程却大有不同，在程序中如果用错了，可能会造成莫名其妙的现象。
      * 执行kill pid命令，系统会发送一个SIGTERM信号给对应的程序。
      * 执行kill -9 pid命令，系统给对应程序发送的信号是SIGKILL，即exit.
      * exit信号不会被系统阻塞，所以kill -9能顺利杀掉进程 */
    //SIGSTOP和SIGKILL信号是不可捕获的,所以下面两句话写了等于没有写
    RegSigHandler(SIGKILL, SIG_IGN);//kill -9 pid
    RegSigHandler(SIGSTOP, SignalHandler);//ctrl+z代表停止

    RegSigHandler(SIGBUS,  SignalHandler);
    RegSigHandler(SIGSEGV, SignalHandler);
    RegSigHandler(SIGILL,  SignalHandler);
}

void SignalReplace()
{
    struct sigaction sa_old;
    struct sigaction sa_new;
    /* do not allow ctrl-c for now... */
    memset(&sa_old, 0, sizeof(struct sigaction));
    memset(&sa_new, 0, sizeof(struct sigaction));
    sa_new.sa_handler = SignalHandler;
    sigemptyset(&sa_new.sa_mask);
    sa_new.sa_flags = 0;
    sigaction(SIGINT, &sa_new, &sa_old );
}


} /**************************** end namespace BASE ****************************/
} /**************************** end namespace MSF  ****************************/
