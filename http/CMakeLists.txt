cmake_minimum_required(VERSION 3.10)
project(MyHttpService)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(MyHttpService http_server.cpp)

target_link_libraries(MyHttpService brpc)