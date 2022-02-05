cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)

set(GAME_NAME "wotcvby")
set(SOURCE_PATH "src")
project(${GAME_NAME})

set(CMAKE_BUILD_TYPE "Debug")

include_directories("src")
include_directories("include")
add_subdirectory("deps/SFGUI")
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
file(GLOB_RECURSE SOURCES "${SOURCE_PATH}/*.cpp")

add_executable(${GAME_NAME} ${SOURCES})
target_link_libraries(${GAME_NAME} sfml-graphics sfml‑network sfml-audio)