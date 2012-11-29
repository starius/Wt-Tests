cmake_minimum_required(VERSION 2.6)

project(Test)

find_package(Boost COMPONENTS date_time regex program_options signals system filesystem thread REQUIRED)

add_executable(test.wt test.cpp)

target_link_libraries(test.wt wt wthttp ${Boost_LIBRARIES})
