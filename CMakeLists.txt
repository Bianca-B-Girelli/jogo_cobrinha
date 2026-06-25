cmake_minimum_required(VERSION 3.15)
project(jogo)

find_package(raylib REQUIRED)


add_executable(${PROJECT_NAME} main.c )
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

