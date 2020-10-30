cmake_minimum_required(VERSION 3.10)

project(back_gal)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include/msvc)
include_directories(include)
link_directories(lib/vc_x64_dll)
add_definitions(-DUNICODE -D_UNICODE)



add_executable(start WIN32 main.cpp icon.rc)