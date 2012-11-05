project(WtTest)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Boost
 COMPONENTS
    date_time
    regex
    program_options
    signals
    system
    filesystem
    thread
  REQUIRED)

include_directories(${Wt_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

add_executable(test.wt test.cpp)

target_link_libraries(test.wt ${Boost_LIBRARIES} wt wthttp wtdbo wtdbosqlite3)
