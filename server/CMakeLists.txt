add_executable(reverb-server main.cpp)

target_include_directories(reverb-server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/libs)

target_compile_definitions(reverb-server PRIVATE ASIO_STANDALONE)
target_link_libraries(reverb-server PRIVATE pthread)
