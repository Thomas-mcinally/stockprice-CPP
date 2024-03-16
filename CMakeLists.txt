cmake_minimum_required(VERSION 3.10)
project(Stockprice)

set(CMAKE_CXX_STANDARD 11)

######### Add custom commands to build OpenSSL from source###########
# NEED TO MODIFY
add_custom_target(openssl
    COMMAND <command to configure OpenSSL>
    COMMAND <command to build OpenSSL>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/openssl-3.2.1
)
include_directories(${CMAKE_SOURCE_DIR}/openssl-3.2.1/include)
link_directories(${CMAKE_SOURCE_DIR}/openssl-3.2.1)

#############################################

add_executable(Stockprice src/main.cpp)
add_dependencies(Stockprice openssl)

target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libcrypto.a ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libssl.a) #depends where libssl.a and libcrypto.a are located after build OpenSSL