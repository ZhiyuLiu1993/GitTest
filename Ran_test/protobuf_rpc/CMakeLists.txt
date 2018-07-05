PROJECT(protobuf-rpc-demp)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-5")
#add_compile_options(-std=c++11)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#link_directories(/usr/lib/x86_64-linux-gnu)
##注意，protobuf版本是3.0及以上
link_libraries(/home/lzy/google_carto_ws/protobuf/build/libprotobuf.a)
include_directories(/usr/include)
set(SRC echo.pb.h myrpc.h rpc_meta.pb.h)
set(LIBMYRPC_SRC ./rpc_meta.pb.cc)
add_library(myrpc ${LIBMYRPC_SRC})
add_executable(server ./echo.pb.cc ./test_myrpc.cpp ${SRC})
target_link_libraries(server libboost_signals.a libboost_system.a myrpc)
add_executable(client ./echo.pb.cc ./test_myrpc_client.cpp ${SRC})
target_link_libraries(client libboost_signals.a libboost_system.a myrpc)


