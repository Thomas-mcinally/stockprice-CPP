cmake_minimum_required(VERSION 3.20)

set(BUILD_SHARED_LIBS OFF) # static linking of included libraries (cpr & libcurl)

project(stockprice)

set(CMAKE_CXX_STANDARD 17)

set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if(WIN32)
    # Install DLLs in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(stockprice main.cpp)

include(FetchContent)

FetchContent_Declare(curl
URL                    https://github.com/curl/curl/releases/download/curl-8_4_0/curl-8.4.0.tar.xz
URL_HASH               SHA256=16c62a9c4af0f703d28bda6d7bbf37ba47055ad3414d70dec63e2e6336f2a82d # the file hash for curl-8.4.0.tar.xz
USES_TERMINAL_DOWNLOAD TRUE)   # <---- This is needed only for Ninja to show download progress
FetchContent_MakeAvailable(curl)
set(CPR_USE_SYSTEM_CURL ON)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                   GIT_TAG 3020c34ae2b732121f37433e61599c34535e68a8)
FetchContent_MakeAvailable(cpr)

target_link_libraries(stockprice PRIVATE cpr::cpr)