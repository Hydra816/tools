cmake_minimum_required(VERSION 3.10)
project(oracle_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# 包含路径
include_directories(
    ${CMAKE_SOURCE_DIR}/include          # 你的头文件
    ${CMAKE_SOURCE_DIR}/src              # 源文件目录（如果有头文件）
)

find_package(SOCI REQUIRED)

# 所有源文件
file(GLOB SOURCES "src/*.cpp")
# 创建可执行文件
add_executable(oracle_demo ${SOURCES})

# 链接库
target_link_libraries(oracle_demo soci_core soci_oracle)