cmake_minimum_required(VERSION 3.8)
project(cs3358_abm_assignment7)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE_DIRECTORIES)

set(SOURCE_FILES
        Assign07Test.cpp
        DPQueue.cpp
        DPQueue.h)

add_executable(cs3358_abm_assignment7 ${SOURCE_FILES})