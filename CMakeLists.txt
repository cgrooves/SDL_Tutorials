cmake_minimum_required(VERSION 3.0)

project(sdl_hello_render)

add_executable(sdl_hello_render main.cpp)

install(TARGETS sdl_hello_render RUNTIME DESTINATION bin)
