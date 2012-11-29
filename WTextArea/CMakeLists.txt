cmake_minimum_required(VERSION 2.6)

project(Test)

find_package(Boost COMPONENTS signals REQUIRED) # date_time regex program_options system filesystem thread

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=gnu++0x -Wall -Wextra -pedantic")
endif()

add_executable(test.wt test.cpp)

target_link_libraries(test.wt wt wthttp ${Boost_LIBRARIES}) # wthttp / wtfcgi # wtdbo wtdbosqlite3 wtdbopostgres #
