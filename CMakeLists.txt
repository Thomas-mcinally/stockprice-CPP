cmake_minimum_required(VERSION 3.10)
project(Stockprice)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Stockprice src/main.cpp)

target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/lib/libssl.a)
target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/lib/libcrypto.a)