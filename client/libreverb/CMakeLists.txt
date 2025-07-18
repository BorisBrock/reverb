add_library(voice SHARED voice.cpp)

target_include_directories(voice PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/libs)

target_compile_definitions(voice PRIVATE ASIO_STANDALONE)
target_link_libraries(voice PRIVATE pthread)
