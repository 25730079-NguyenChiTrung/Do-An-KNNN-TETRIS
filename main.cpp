/*
 * TETRIS CONSOLE GAME
 * Game xep hinh Tetris chay tren console
 * Viet bang C++ su dung struct
 * Danh cho sinh vien dai hoc nam 2
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include "piece.h"
#include "board.h"
#include "display.h"
#include "input.h"

using namespace std;

// ===================== HAM KHOI TAO GAME =====================

// Khoi tao trang thai game ban dau
void initGame(GameState &game) {
    // Khoi tao bang choi
    initBoard(game);
    
    // Khoi tao random seed
    srand(time(NULL));
    
    // Tao khoi dau tien va khoi tiep theo
    game.currentPiece = createPiece();
    game.nextPiece = createPiece();
}

// ===================== HAM XU LY HARD DROP =====================

// Tha khoi roi thang xuong day
void hardDrop(GameState &game) {
    while (moveDown(game)) {
        game.score += 2;  // Cong them diem khi hard drop
    }
}

// ===================== VONG LAP GAME CHINH =====================

void gameLoop(GameState &game) {
    long long lastFallTime = getCurrentTimeMs();
    
    while (!game.gameOver) {
        // Ve man hinh
        draw(game);
        
        // Xu ly input
        if (keyPressed()) {
            char key = getKey();
            
            switch (key) {
                case 'a':
                case 'A':
                    moveLeft(game);
                    break;
                case 'd':
                case 'D':
                    moveRight(game);
                    break;
                case 'w':
                case 'W':
                    rotatePiece(game);
                    break;
                case 's':
                case 'S':
                    if (moveDown(game)) {
                        game.score += 1;  // Cong diem khi soft drop
                    }
                    break;
                case ' ':  // Space - hard drop
                    hardDrop(game);
                    break;
                case 'q':
                case 'Q':
                    game.gameOver = true;
                    break;
                    
                // Xu ly phim mui ten (Linux/Mac)
                #ifndef _WIN32
                case 27:  // ESC sequence cho phim mui ten
                    if (keyPressed()) {
                        getKey();  // Bo qua '['
                        if (keyPressed()) {
                            char arrow = getKey();
                            switch (arrow) {
                                case 'A': rotatePiece(game); break;      // Up
                                case 'B':                                 // Down
                                    if (moveDown(game)) game.score += 1;
                                    break;
                                case 'C': moveRight(game); break;         // Right
                                case 'D': moveLeft(game); break;          // Left
                            }
                        }
                    }
                    break;
                #endif
            }
        }
        
        // Tu dong roi xuong theo toc do hien tai
        long long currentTime = getCurrentTimeMs();
        if (currentTime - lastFallTime >= game.currentSpeed) {
            if (!moveDown(game)) {
                // Khoi da cham day hoac khoi khac
                placePiece(game);
                
                // Xoa hang va cap nhat diem
                int lines = removeLines(game);
                updateScoreAndSpeed(game, lines);
                
                // Sinh khoi moi
                spawnNewPiece(game);
            }
            lastFallTime = currentTime;
        }
        
        // Delay nho de giam tai CPU
        sleepMs(30);
    }
}

// ===================== HAM MAIN =====================

int main() {
    // Khoi tao game
    GameState game;
    initGame(game);
    
    // Chay vong lap game
    gameLoop(game);
    
    // Hien thi man hinh ket thuc
    drawGameOver(game);
    
    // Cho nguoi choi nhan phim
    getKey();
    
    return 0;
}
