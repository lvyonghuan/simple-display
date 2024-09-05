cmake_minimum_required(VERSION 3.27)
project(simple_display)

set(CMAKE_CXX_STANDARD 17)

add_executable(simple_display main.cpp)

# 添加链接库
target_link_libraries(simple_display setupapi cfgmgr32)

if (WIN32)
    target_link_libraries(simple_display -mwindows)
endif