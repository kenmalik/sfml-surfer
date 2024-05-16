cmake_minimum_required(VERSION 3.10)
project(Review_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK
    "${PROJECT_BINARY_DIR}/compile_commands.json"
    "${PROJECT_SOURCE_DIR}/compile_commands.json"
    SYMBOLIC
)

add_executable(Main src/main.cpp)

target_include_directories(Main PRIVATE include)

target_link_libraries(Main PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
