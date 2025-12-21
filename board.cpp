/*
 * THANH VIEN 3: XU LY BANG CHOI
 * File: board.cpp
 *
 * Nhiem vu:
 * - Khoi tao bang choi
 * - Dat khoi vao bang
 * - Xoa cac hang da day
 * - Cap nhat diem va toc do
 */

#include "board.h"
#include "piece.h"

// Khoi tao bang choi (xoa toan bo bang)
void initBoard(GameState &game) {
    // Xoa bang choi
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            game.board[i][j] = 0;
        }
    }
    
    // Khoi tao cac gia tri ban dau
    game.score = 0;
    game.level = 1;
    game.linesCleared = 0;
    game.baseSpeed = 500;      // 500ms cho moi lan roi
    game.currentSpeed = game.baseSpeed;
    game.gameOver = false;
}

// Dat khoi hien tai vao bang
void placePiece(GameState &game) {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (game.currentPiece.shape[i][j] == 1) {
                int boardX = game.currentPiece.x + j;
                int boardY = game.currentPiece.y + i;
                if (boardY >= 0 && boardY < BOARD_HEIGHT &&
                    boardX >= 0 && boardX < BOARD_WIDTH) {
                    game.board[boardY][boardX] = game.currentPiece.type + 1;
                }
            }
        }
    }
}

// Xoa cac hang da day va tra ve so hang da xoa
int removeLines(GameState &game) {
    int linesRemoved = 0;
    
    // Duyet tu duoi len
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        bool fullLine = true;
        
        // Kiem tra hang co day khong
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (game.board[i][j] == 0) {
                fullLine = false;
                break;
            }
        }
        
        if (fullLine) {
            linesRemoved++;
            
            // Di chuyen tat ca cac hang phia tren xuong
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    game.board[k][j] = game.board[k - 1][j];
                }
            }
            
            // Xoa hang tren cung
            for (int j = 0; j < BOARD_WIDTH; j++) {
                game.board[0][j] = 0;
            }
            
            // Kiem tra lai hang hien tai (vi cac hang da di chuyen xuong)
            i++;
        }
    }
    
    return linesRemoved;
}

// Cap nhat diem va toc do sau khi xoa hang
void updateScoreAndSpeed(GameState &game, int linesRemoved) {
    if (linesRemoved == 0) return;
    
    // Tinh diem (nhieu hang hon = diem cao hon)
    int points[] = {0, 100, 300, 500, 800};  // 1, 2, 3, 4 hang
    game.score += points[linesRemoved] * game.level;
    
    // Cap nhat tong so hang da xoa
    game.linesCleared += linesRemoved;
    
    // Tang level moi 10 hang
    game.level = 1 + game.linesCleared / 10;
    
    // Tang toc do (giam thoi gian delay)
    // Toc do = baseSpeed - (level * 40), toi thieu la 100ms
    game.currentSpeed = game.baseSpeed - (game.level - 1) * 40;
    if (game.currentSpeed < 100) {
        game.currentSpeed = 100;
    }
}

// Sinh khoi moi
void spawnNewPiece(GameState &game) {
    game.currentPiece = game.nextPiece;
    game.nextPiece = createPiece();
    
    // Kiem tra game over
    if (!canPlace(game, game.currentPiece, game.currentPiece.x, game.currentPiece.y)) {
        game.gameOver = true;
    }
}
