cmake_minimum_required(VERSION 3.5)
project(tinyhttp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -g -Wall -O2")
#set(CMAKE_PREFIX_PATH )

add_executable(tinyhttp httpd.c)

add_executable(simpleclient simpleclient.c)
