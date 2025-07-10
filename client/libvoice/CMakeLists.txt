add_library(voice SHARED voice.cpp)

target_include_directories(voice PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
