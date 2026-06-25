cmake_minimum_required(VERSION 3.15)
project(jogo_cobrinha)

find_package(raylib REQUIRED)


add_executable(${PROJECT_NAME} jogo_cobrinha.c )
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

