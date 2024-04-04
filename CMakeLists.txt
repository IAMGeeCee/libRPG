cmake_minimum_required(VERSION 4.5)
project(libRPG)


# Dependencies
include(FetchContent)

set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") 

# Define your library
add_library(libRPG STATIC "src/Game.cpp" "src/Player.cpp")

# Include paths for the library
target_include_directories(libRPG PUBLIC src)

# Link your library with raylib
target_link_libraries(libRPG raylib)

# Define your main application
add_executable(test-game
    test-game/main.cpp
)

# Link your application with your library
target_link_libraries(test-game PRIVATE libRPG)

