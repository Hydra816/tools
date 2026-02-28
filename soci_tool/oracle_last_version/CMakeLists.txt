cmake_minimum_required(VERSION 3.10)
project(oracle_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# 包含路径
include_directories(
    ${CMAKE_SOURCE_DIR}/include/entities       # 你的头文件
    ${CMAKE_SOURCE_DIR}/include/oracle_db
    ${CMAKE_SOURCE_DIR}/src              # 源文件目录（如果有头文件）
)

find_package(SOCI REQUIRED)

# 所有源文件
file(GLOB SOURCES "src/*.cpp")
#创建库
add_library(oracle_api SHARED ${SOURCES})
# 创建可执行文件
#add_executable(oracle_demo ${SOURCES})

# 链接库
target_link_libraries(oracle_api soci_core soci_oracle)



# cmake_minimum_required(VERSION 3.10)
# project(oracle_api)

# set(CMAKE_CXX_STANDARD 17)

# # 包含路径
# include_directories(
#     ${CMAKE_SOURCE_DIR}/include
#     ${CMAKE_SOURCE_DIR}/src
#     /install/soci/include
#     /opt/oracle/db01/app/oracle/product/10.2.0/rdbms/public
# )

# file(GLOB SOURCES "src/*.cpp")

# # 创建静态库
# add_library(oracle_api STATIC ${SOURCES})

# # ================= 关键：使用 OBJECT 库 + 合并 =================
# # 方法A：先创建对象库，再创建合并的静态库
# add_library(oracle_api_obj OBJECT ${SOURCES})
# target_include_directories(oracle_api_obj PRIVATE
#     /install/soci/include
#     /opt/oracle/db01/app/oracle/product/10.2.0/rdbms/public
# )

# # 创建真正的静态库，包含所有对象
# add_library(oracle_api_merged STATIC $<TARGET_OBJECTS:oracle_api_obj>)

# # 手动链接依赖（仍然需要使用者链接）
# target_link_libraries(oracle_api_merged
#     /install/soci/lib64/libsoci_core.so
#     /install/soci/lib64/libsoci_oracle.so
#     /opt/oracle/db01/app/oracle/product/10.2.0/lib/libclntsh.so
#     pthread dl m
# )

# # 设置输出名称
# set_target_properties(oracle_api_merged PROPERTIES OUTPUT_NAME "oracle_api")