cmake_minimum_required(VERSION 4.4.5)

project(platformer LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries" FORCE)

# SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Executable
add_executable(platformer
    src/Action.cpp
    src/Animation.cpp
    src/Collision.cpp
    src/Debug.cpp
    src/Entity.cpp
    src/EntityManager.cpp
    src/Game.cpp
    src/Helper.cpp
    src/LevelScene.cpp
    src/Scene.cpp
    src/main.cpp
    src/asset_manager.cpp
    src/utils/logger.cpp
)
target_include_directories(platformer PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)
target_link_libraries(platformer PRIVATE
    SFML::Graphics
)

# Output executable to bin/
set_target_properties(platformer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Copy assets after building
add_custom_command(TARGET platformer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:platformer>/assets"
)
# Copy runtime DLL dependencies after building
add_custom_command(TARGET platformer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_RUNTIME_DLLS:platformer>"
        "$<TARGET_FILE_DIR:platformer>"
    COMMAND_EXPAND_LISTS
)
