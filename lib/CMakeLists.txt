cmake_minimum_required(VERSION 3.15 FATAL_ERROR)      # 指定 cmake 的最小版本
cmake_policy(VERSION 3.15)
project(MSF_LIB_PROJECT)                                    # 设置项目名称

# 加入一个配置头文件,用于处理 CMake 对源码的设置
configure_file (
    "${PROJECT_SOURCE_DIR}/conf/Config.h.in"
    "${PROJECT_SOURCE_DIR}/conf/Config.h"
    )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
include (${CMAKE_MODULE_PATH}/FindNUMA.cmake)
include (${CMAKE_MODULE_PATH}/utils.cmake)
#include (${CMAKE_MODULE_PATH}/FindProtobuf.cmake)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wl,-rpath=/tools/lib64 -Wl,#--dynamic-linker=/tools/lib/ld-2.17.so")

# -std=gnu++11 与 -std=c++11 有什么区别？
# https://blog.csdn.net/juan202/article/details/79968898?utm_source=blogxgwz4
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -fPIC -O3 -Wall -g -ggdb")

# 宏定义
add_definitions(-DMSF_UNIX_IPC)

# 设置包含的头文件目录
# 其他方式: set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/
)

#set(CMAKE_VERBOSE_MAKEFILE ON)
# 是否使开启debug
# 执行cmake -DCMAKE_BUILD_TYPE=Debug（或Release)
# Debug版会使用参数-g；Release版使用-O3 –DNDEBUG
# 在执行cmake时增加参数即可，例如cmake -DDEBUG_mode=ON

option(DEBUG_mode "ON for debug or OFF for release" ON)
IF(DEBUG_mode)
    message(STATUS "Current project compile in debug mode.") 
    add_definitions(-DDEBUG)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -fPIC -O0 -Wall -g -ggdb")
ELSE()
    message(STATUS "Current project compile in release mode.") 
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -fPIC -O3 -Wall")
ENDIF()

add_subdirectory (base msf_base)
add_subdirectory (encrypt msf_encrypt)
add_subdirectory (sock msf_sock)
add_subdirectory (event msf_event)
add_subdirectory (agent msf_agent)

aux_source_directory (. DIR_SRCS)
add_library (msf SHARED ${DIR_SRCS})

SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/usr)                        # 安装路径前缀 /home/xxx/usr
#INSTALL(DIRECTORY doc/ DESTINATION share/msf)                  # 安装项目文档
#INSTALL(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION lib)    # 二进制安装到 usr/bin