@echo off
rem Change to the specified directory
cd /d "C:\Users\George\Code\libRPG\Build"

rem Run CMake
cmake ..

rem Build using CMake
cmake --build .

rem Check the exit code of the build command
if %errorlevel% neq 0 (
    echo Build failed.
    exit /b %errorlevel%
)

rem Change to the Debug directory
cd Debug

rem Run Underworld.exe
test-game.exe

rem Put directory back
cd ../../
