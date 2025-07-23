cmake_minimum_required(VERSION 3.10)
project(MyKafkaApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)


# 设置 include 路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 设置库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

# 将所有源文件加进来
set(SOURCE_FILES
    src/test.cpp
    src/vlr_kafka_service.cpp
)

add_executable(MyKafkaApp ${SOURCE_FILES})

# 链接你放进来的 so 库
target_link_libraries(MyKafkaApp
    cppkafka
    rdkafka
    pthread
)
