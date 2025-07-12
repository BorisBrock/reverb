add_executable(reverb-server main.cpp)

target_include_directories(reverb-server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(reverb-server PRIVATE nng::nng Threads::Threads)
