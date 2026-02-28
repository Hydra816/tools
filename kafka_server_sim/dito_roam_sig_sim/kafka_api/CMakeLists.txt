message("kafka_api building..")

#include 路径 和 库路径都采用当前目录 kafka_api/include 和 kafka_api/lib
# 设置 include 路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vlr_adaptor/vlr/include
    ${PROJECT_SOURCE_DIR}/oss_api/c/utility_api/include
    )

# 设置库路径
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)


add_library(kafka_api
${CMAKE_CURRENT_SOURCE_DIR}/src/kafka_service.cpp
)

target_include_directories(kafka_api PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 链接so 库
target_link_libraries(kafka_api
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcppkafka.so.0.3.1
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/librdkafka.so.1
    pthread
)

