add_library(chat SHARED chat.cpp)

target_include_directories(chat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(chat PUBLIC nng::nng Threads::Threads)
