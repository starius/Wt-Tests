cmake_minimum_required(VERSION 2.6)

project(Test)
SET (CMAKE_VERBOSE_MAKEFILE ON)

SET (CMAKE_CXX_COMPILER "g++-4.7")
SET (CMAKE_BUILD_TYPE "Debug")
SET (CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -pedantic -march=native -pthread -Wall -Wextra -O0 -ggdb3 -DDEBUG")

find_package(Boost COMPONENTS date_time regex program_options signals system filesystem thread REQUIRED)

add_executable(test.wt test.cpp)

target_link_libraries(test.wt wt wthttp ${Boost_LIBRARIES}) # wthttp / wtfcgi # wtdbo wtdbosqlite3 wtdbopostgres #
