cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(Stockprice)

add_executable(Stockprice src/main.cpp src/get_ticker_statistics.cpp)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(OPENSSL_CONFIGURE_TRIPLET "darwin64-arm64-cc")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(OPENSSL_CONFIGURE_TRIPLET "darwin64-x86_64-cc")
    else()
        message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
    endif()

    add_custom_target(openssl
        COMMAND ./Configure no-shared no-asm no-zlib no-psk no-srp enable-rc5 ${OPENSSL_CONFIGURE_TRIPLET}
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/openssl-3.2.1
    )
    add_dependencies(Stockprice openssl)
    target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libcrypto.a ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libssl.a)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "AMD64")
        set(OPENSSL_CONFIGURE_TRIPLET "VC-WIN64A")
    else()
        message(FATAL_ERROR "Unsupported architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
    endif()

    add_custom_target(openssl
        COMMAND perl Configure no-shared no-asm no-zlib no-psk no-srp enable-rc5 ${OPENSSL_CONFIGURE_TRIPLET}
        COMMAND nmake
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/openssl-3.2.1
    )
    add_dependencies(Stockprice openssl)
    target_link_libraries(Stockprice ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libcrypto.lib ${CMAKE_SOURCE_DIR}/openssl-3.2.1/libssl.lib)
else()
    message(FATAL_ERROR "Unsupported system: ${CMAKE_HOST_SYSTEM_NAME}")
endif()

include_directories(${CMAKE_SOURCE_DIR}/openssl-3.2.1/include)