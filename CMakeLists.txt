cmake_minimum_required(VERSION 4.0)

project(platformer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)

add_executable(platformer main.cpp)

target_link_libraries(platformer PRIVATE
    SFML::Graphics
)
