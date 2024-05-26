cmake_minimum_required(VERSION 3.10)
project(Review_Project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(CREATE_LINK "${PROJECT_BINARY_DIR}/compile_commands.json"
     "${PROJECT_SOURCE_DIR}/compile_commands.json" SYMBOLIC)

set(SOURCES src/main.cpp src/surfer.cpp src/scanner.cpp src/token.cpp src/p.cpp)
add_executable(Main ${SOURCES})

target_include_directories(Main PRIVATE include)

include(FetchContent)

FetchContent_Declare(
  GUI_Library
  GIT_REPOSITORY git@github.com:kenmalik/gui-library.git
  GIT_TAG c2e4af98d7a04f73fc5cec8cf8ef7ccb1ad50d59)

FetchContent_MakeAvailable(GUI_Library)

target_include_directories(Main PUBLIC ${GUI_Library_SOURCE_DIR}/include)
target_link_libraries(Main PUBLIC sfml-graphics sfml-window sfml-system
                                  sfml-audio gui-library)

find_package(
  SFML 2.5
  COMPONENTS graphics audio
  REQUIRED)
