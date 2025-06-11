cmake_minimum_required(VERSION 3.22)    #版本号，无所谓
project(system LANGUAGES CXX)           #第一个参数为文件名，第二个参数是语言，第三个参数是具体语言类型，CXX代表c++

# 添加调试符号和设置优化级别
set(CMAKE_BUILD_TYPE Debug)             #生成调试信息
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")    #在编译参数中加入-g生成调试信息

include_directories(include)        #头文件目录，代表下方的cpp文件在编译时，编译指令中添加的搜索头文件的地址
add_executable(system src/main.cpp src/account.cpp src/AccountException.cpp src/date.cpp src/usr.cpp )
#src代表目录，后面的cpp代表文件，前面的system代表编译生成的可执行文件名。


#为什么要这么干？因为这样将编译输出（build)，头文件(include)，以及源代码(src)分成三个模块，更加干净的工作区。