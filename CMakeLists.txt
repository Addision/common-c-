cmake_minimum_required(VERSION 2.8)

project(TestCommon)

add_definitions(-D__LINUX__)

include_directories(../lib/rapidjson/include ../lib/libevent/include ./ )

link_directories()

set(SOURCE_FILE TestCommon.cpp Config.cpp Thread.cpp Log.cpp ThreadPool.cpp Util.cpp Timer.cpp)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -o2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(TestCommon ${SOURCE_FILE})

target_link_libraries(TestCommon  libevent.a libevent_core.a pthread)
