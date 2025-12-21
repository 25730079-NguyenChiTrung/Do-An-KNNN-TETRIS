@echo off
REM Build script for Tetris game on Windows

echo Compiling Tetris...
g++ -std=c++17 -Wall -o tetris.exe main.cpp piece.cpp board.cpp display.cpp input.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! tetris.exe created.
    echo.
    echo Run the game with: .\tetris.exe
    echo Or simply: tetris
) else (
    echo.
    echo Build failed!
    exit /b 1
)
