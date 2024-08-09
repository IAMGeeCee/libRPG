cmake_minimum_required(VERSION 3.28)
project(libRPG)

# Set version of raylib
set(RAYLIB_VERSION 5.0)

# Enable compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# FetchContent module to download raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
# Disable building raylib examples
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
# Make raylib available
FetchContent_MakeAvailable(raylib)

# Define your library
add_library(libRPG STATIC src/Game.cpp src/Player.cpp src/Map.cpp src/InteractableObject.cpp src/Entity.cpp)

# Include paths for the library
target_include_directories(libRPG PUBLIC src)

# Link your library with raylib
target_link_libraries(libRPG PUBLIC raylib)

# Define your main application
add_executable(test-game test-game/main.cpp)

# Link your application with your library and raylib
target_link_libraries(test-game PRIVATE libRPG raylib)