add_executable(reverb-server main.cpp)

target_include_directories(reverb-server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/libs)

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(reverb-server PRIVATE pthread Boost::system)
