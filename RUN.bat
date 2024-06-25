@echo off
rem Change to the specified directory
cd /d "C:\Users\George\Dev\libRPG\Build" || (
    echo Failed to change directory to Build.
    exit /b 1
)

rem Run CMake to configure the project
cmake .. || (
    echo CMake configuration failed.
    cd ..
    exit /b 1
)

rem Build using CMake
cmake --build . || (
    echo Build failed.
    cd ..
    exit /b 1
)

rem Check if Debug directory exists and change to it
if exist Debug (
    cd Debug
) else (
    echo Debug directory does not exist.
    cd ..
    exit /b 1
)

rem Run the executable
if exist test-game.exe (
    test-game.exe || (
        echo test-game.exe execution failed.
        cd ..
        exit /b 1
    )
) else (
    echo test-game.exe not found.
    cd ..
    exit /b 1
)

rem Change back to the initial directory
cd ../../
