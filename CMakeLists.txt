cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(Stockprice)

if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(OPENSSL_CONFIGURE_TRIPLET "darwin64-arm64-cc")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(OPENSSL_CONFIGURE_TRIPLET "darwin64-x86_64-cc")
else()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
endif()
add_custom_target(openssl
    COMMAND ./Configure no-shared no-zlib enable-rc5 ${OPENSSL_CONFIGURE_TRIPLET}
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/openssl-3.2.1
)
include_directories(${CMAKE_SOURCE_DIR}/openssl-3.2.1/include)

add_executable(Stockprice src/main.cpp src/get_ticker_statistics.cpp)
add_dependencies(Stockprice openssl)

target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libcrypto.a ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libssl.a)