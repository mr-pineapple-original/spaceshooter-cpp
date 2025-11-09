@echo off
SETLOCAL ENABLEDELAYEDEXPANSION

REM Project paths
SET "BUILD_DIR=build"
SET "EXECUTABLE=SpaceShooter.exe"

REM Create build directory if missing
IF NOT EXIST "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

REM Enter build directory
cd "%BUILD_DIR%"

REM Run CMake configuration if no cache exists
IF NOT EXIST "CMakeCache.txt" (
    echo [CMake] Configuring project...
    cmake ..
)

REM Build using all available CPU cores
echo [Build] Compiling...
cmake --build . -- /m

REM Go back to project root
cd ..

REM Run the compiled program if it exists
IF EXIST "%BUILD_DIR%\%EXECUTABLE%" (
    echo [Run] Launching program...
    "%BUILD_DIR%\%EXECUTABLE%"
) ELSE (
    echo [Error] Executable not found: %BUILD_DIR%\%EXECUTABLE%
    exit /b 1
)

