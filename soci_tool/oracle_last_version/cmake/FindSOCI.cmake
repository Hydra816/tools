INCLUDE(ExternalProject)

# 配置SOCI源目录和安装目录
set(SOCI_SOURCES_DIR ${THIRD_PARTY_PATH}/soci)
set(SOCI_INSTALL_DIR ${THIRD_PARTY_PATH}/install/soci)
set(SOCI_INCLUDE_DIR "${SOCI_INSTALL_DIR}/include" CACHE PATH "SOCI include directory." FORCE)
set(ENV{ORACLE_HOME} "/opt/oracle/db01/app/oracle/product/10.2.0")
set(ORACLE_INCLUDE_DIR
    "$ENV{ORACLE_HOME}/rdbms/public"
    CACHE PATH "Oracle include dir"
)
# 定义Oracle依赖路径（需根据实际环境调整）
#set(ORACLE_INCLUDE_DIR "${ORACLE_INCLUDE_DIR}" CACHE PATH "Oracle include directory (e.g. /usr/include/oracle/19.3/client64)")
#set(ORACLE_LIBRARY_DIR "${ORACLE_LIB}" CACHE PATH "Oracle library directory (e.g. /usr/lib/oracle/19.3/client64/lib)")

find_library(ORACLE_CLIENT_LIBRARY
    NAMES clntsh
    PATHS
        $ENV{ORACLE_HOME}/lib
        $ENV{ORACLE_HOME}/lib64
)

ExternalProject_Add(
        extern_soci
        ${EXTERNAL_PROJECT_LOG_ARGS}
        # SOCI源码包路径（请替换为实际版本）
        URL             ${PROJECT_SOURCE_DIR}/third-party/soci-4.0.1.tar.gz
        PREFIX          ${SOCI_SOURCES_DIR}
        # 传递编译器和编译选项
        CMAKE_ARGS      -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                        # 安装路径配置
                        -DCMAKE_INSTALL_PREFIX=${SOCI_INSTALL_DIR}
                        -DCMAKE_INSTALL_LIBDIR=${SOCI_INSTALL_DIR}/lib
                        # 仅启用Oracle，禁用其他数据库
                        -DWITH_ORACLE=ON
                        -DWITH_POSTGRESQL=OFF
                        # 禁用测试和示例
                        -DSOCI_TESTS=OFF
                        -DSOCI_EXAMPLES=OFF
                        # 静态库配置
                        -DBUILD_SHARED_LIBS=OFF
                        -DCMAKE_CXX_STANDARD=17
                        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                        -DCMAKE_MACOSX_RPATH=ON
                        # Oracle依赖配置：显式传递路径
                        #-DORACLE_INCLUDE_DIR=${ORACLE_INCLUDE_DIR}
                        #-DORACLE_LIBRARY_DIR=${ORACLE_LIBRARY_DIR}
                        # 也可以尝试直接指定Oracle Home
                        -DORACLE_HOME=${ORACLE_HOME}
                        # 构建类型
                        -DCMAKE_BUILD_TYPE=${THIRD_PARTY_BUILD_TYPE}
                        ${EXTERNAL_OPTIONAL_ARGS}
        # 缓存关键路径参数
        CMAKE_CACHE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${SOCI_INSTALL_DIR}
                         -DCMAKE_INSTALL_LIBDIR:PATH=${SOCI_INSTALL_DIR}/lib
                         -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
                         -DCMAKE_BUILD_TYPE:STRING=${THIRD_PARTY_BUILD_TYPE}
                         #-DORACLE_INCLUDE_DIR:PATH=${ORACLE_INCLUDE_DIR}
                         ##-DORACLE_LIBRARY_DIR:PATH=${ORACLE_LIBRARY_DIR}
)

# 定义SOCI库文件路径
set(SOCI_CORE_LIBRARY "${SOCI_INSTALL_DIR}/lib64/libsoci_core.a" CACHE FILEPATH "SOCI core library." FORCE)
set(SOCI_ORACLE_LIBRARY "${SOCI_INSTALL_DIR}/lib64/libsoci_oracle.a" CACHE FILEPATH "SOCI Oracle library." FORCE)

# 创建SOCI核心库导入目标
add_library(soci_core STATIC IMPORTED GLOBAL)
set_property(TARGET soci_core PROPERTY IMPORTED_LOCATION ${SOCI_CORE_LIBRARY})
add_dependencies(soci_core extern_soci)
target_include_directories(soci_core INTERFACE ${SOCI_INCLUDE_DIR})

# 创建SOCI Oracle库导入目标（依赖核心库）
add_library(soci_oracle STATIC IMPORTED GLOBAL)
set_property(TARGET soci_oracle PROPERTY IMPORTED_LOCATION ${SOCI_ORACLE_LIBRARY})
add_dependencies(soci_oracle extern_soci)
target_link_libraries(soci_oracle INTERFACE soci_core ${ORACLE_CLIENT_LIBRARY} dl)
target_include_directories(soci_oracle INTERFACE ${SOCI_INCLUDE_DIR} ${ORACLE_INCLUDE_DIR})
