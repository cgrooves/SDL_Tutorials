cmake_minimum_required(VERSION 3.0)
set(project_name sdl_hello_render)
project(${project_name})

add_executable(${project_name} main.cpp)

target_link_libraries( ${project_name} SDL2 )

add_custom_target(copy_res_directory ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/res"
    COMMENT "Copy res directory to build tree"
    VERBATIM)
