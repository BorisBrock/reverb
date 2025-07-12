cmake_minimum_required(VERSION 3.15)
project(reverb VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(nng QUIET CONFIG)
if(NOT nng_FOUND)
    message(STATUS "nng not found, fetching...")
    FetchContent_Declare(
        nng
        GIT_REPOSITORY https://github.com/nanomsg/nng.git
        GIT_TAG v1.7.1
    )
    set(NNG_TESTS OFF CACHE BOOL "" FORCE)
    set(NNG_TOOLS OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(nng)
    if(TARGET nng AND NOT TARGET nng::nng)
        add_library(nng::nng ALIAS nng)
    endif()
endif()

find_package(Threads REQUIRED)

add_subdirectory(client/libvoice)
add_subdirectory(client/libchat)
add_subdirectory(server)
