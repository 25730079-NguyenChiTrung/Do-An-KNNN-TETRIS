@echo off
REM Build and run script for Tetris game on Windows

echo Compiling Tetris...
g++ -std=c++17 -Wall -o tetris.exe main.cpp piece.cpp board.cpp display.cpp input.cpp

if %ERRORLEVEL% EQU 0 (
    echo Build successful! Starting game...
    echo.
    tetris.exe
) else (
    echo Build failed!
    pause
    exit /b 1
)
