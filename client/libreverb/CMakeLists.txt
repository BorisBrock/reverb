add_library(voice SHARED voice.cpp)

target_include_directories(voice PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/libs)

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(voice PRIVATE pthread Boost::system)
