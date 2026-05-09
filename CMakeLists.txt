cmake_minimum_required(VERSION 3.10)
project(DartMaths)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(game PRIVATE lib)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(DartMaths ${SOURCES})

target_link_libraries(DartMaths raylib opengl32 gdi32 winmm)

add_custom_command(TARGET DartMaths POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:DartMaths>/assets
)