cmake_minimum_required(VERSION 3.10)
project(Stockprice)

set(CMAKE_CXX_STANDARD 11)

# ######### Build OpenSSL from source ###########
# add_custom_target(openssl
#     COMMAND ./Configure darwin64-arm64-cc #Modify later to specify architecture - see https://wiki.openssl.org/index.php/Compilation_and_Installation
#     COMMAND make
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/openssl-3.2.1
# )
include_directories(${CMAKE_SOURCE_DIR}/openssl-3.2.1/include)

#############################################

add_executable(Stockprice src/main.cpp)
# add_dependencies(Stockprice openssl)

target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libcrypto.a ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libssl.a) #depends where libssl.a and libcrypto.a are located after build OpenSSL