/*
 * THANH VIEN 1: CAU TRUC DU LIEU & HINH DANG KHOI
 * File: structs.h
 * 
 * Nhiem vu:
 * - Dinh nghia cac hang so game
 * - Tao struct Piece va GameState
 * - Dinh nghia 7 hinh dang khoi Tetromino
*/

#ifndef STRUCTS_H
#define STRUCTS_H

//HANG SO GAME
const int BOARD_WIDTH = 10; // Chieu rong bang (10 cot)
const int BOARD_HEIGHT = 20; // Chieu cao bang (20 hang)
const int PIECE_SIZE = 4;  // Kich thuoc toi da cua 1 khoi (4x4)

// Struct dai dien cho 1 khoi Tetris (Tetromino)
struct Piece {
    int shape[PIECE_SIZE][PIECE_SIZE];  // Hinh dang khoi (ma tran 4x4)
    int x, y;                           // Vi tri cua khoi tren bang
    int type;                           // Loai khoi (0-6)
    char symbol;                        // Ky tu hien thi 
};

// Struct chua trang thai game
struct GameState {
    int board[BOARD_HEIGHT][BOARD_WIDTH]; // Bang choi (0 = trong, 1+ = co khoi)
    Piece currentPiece;                   // Khoi dang roi  
    Piece nextPiece; 
    int score;                              
    int level;                              
    int linesCleared;                       
    int baseSpeed;                          
    int currentSpeed;                      
    bool gameOver;                                         
};

// HINH DANG 7 KHOI TETRIS
// Moi khoi la ma tran 4x4, 1 = co o vuong, 0 = trong
const int SHAPES[7][PIECE_SIZE][PIECE_SIZE] = {
    // I - Thanh dai
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
 
    // O - Hinh vuong
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },

    // T - Hinh chu T
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    
    // S - Hinh chu S
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },

    // Z - Hinh chu Z  
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
   
    // J - Hinh chu J
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    },
  
    // L - Hinh chu L
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

// Ky tu hien thi cho moi loai khoi
const char PIECE_SYMBOLS[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
#endif