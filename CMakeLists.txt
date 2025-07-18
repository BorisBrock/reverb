cmake_minimum_required(VERSION 3.15)
project(reverb VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

add_subdirectory(client/libvoice)
add_subdirectory(server)
