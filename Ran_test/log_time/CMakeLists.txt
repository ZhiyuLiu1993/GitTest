cmake_minimum_required(VERSION 3.8)
project(Cliontest2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp mylog.h)
add_executable(Cliontest2 ${SOURCE_FILES})
target_link_libraries(Cliontest2 pthread)