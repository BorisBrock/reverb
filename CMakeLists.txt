cmake_minimum_required(VERSION 3.15)
project(reverb VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export all symbols automatically when building shared libraries on Windows
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_subdirectory(client/libvoice)
add_subdirectory(client/libchat)
