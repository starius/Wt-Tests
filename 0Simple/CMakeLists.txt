cmake_minimum_required(VERSION 2.6)

project(Test)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_COMPILER "g++-4.7")

#set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -pedantic -Wall -Wextra -O0 -ggdb3 -DDEBUG")

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -pedantic -Wall -Wextra -march=core2 -O2 -g0 -DNDEBUG -UNDEBUG -pthread -s")

#find_package(Boost COMPONENTS date_time regex program_options signals system filesystem thread REQUIRED)
find_package(Boost COMPONENTS REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src ${Wt_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${Other_Directory})
link_directories(/usr/lib /usr/local/lib ${CMAKE_SOURCE_DIR}/src ${Boost_LIBRARY_DIRS})

add_executable(test.wt test.cpp)

target_link_libraries(test.wt wt wthttp ${Boost_LIBRARIES}) # wthttp / wtfcgi # wtdbo wtdbosqlite3 wtdbopostgres #

