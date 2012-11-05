cmake_minimum_required(VERSION 2.6)

project(Test)

find_package(Boost COMPONENTS date_time regex program_options signals system filesystem thread REQUIRED)

#include_directories(${Wt_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
include_directories(/usr/include /usr/local/include)

add_executable(test.wt test.cpp)

target_link_libraries(test.wt wt wthttp ${Boost_LIBRARIES}) # wthttp / wtfcgi # wtdbo wtdbosqlite3 wtdbopostgres # 
