cmake_minimum_required(VERSION 3.5)
project(SongCompare)

#set(CMAKE_CXX_STANDARD 11)

add_executable(SongCompare main.cpp Features.cpp Features.h Num.cpp Num.h Comparing.cpp Comparing.h)
target_link_libraries(SongCompare -lessentia -lsamplerate)
#add_library(songcmp SHARED Features.cpp Features.h Num.cpp Num.h Comparing.cpp Comparing.h)
#target_link_libraries(songcmp -lessentia)
