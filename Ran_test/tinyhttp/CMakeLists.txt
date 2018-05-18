cmake_minimum_required(VERSION 3.10)
project(tinyhttp)

set(CMAKE_C_STANDARD 11)

add_executable(tinyhttp httpd.c)

add_executable(simpleclient simpleclient.c)
