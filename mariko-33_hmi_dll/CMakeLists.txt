cmake_minimum_required(VERSION 3.10)

project(mariko-33_hmi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(mariko-33_hmi SHARED mariko-33_hmi.cpp)