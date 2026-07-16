cmake_minimum_required(VERSION 3.15)
project(jogo_cobrinha)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} jogo_cobrinha.c )
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/imagens"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/imagens"
    COMMENT "Copying assets folder to the build directory..."
)