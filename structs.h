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

const int BOARD_WIDTH = 10; 
const int BOARD_HEIGHT = 20;
const int PIECE_SIZE = 4;  

struct Piece {
    int shape[PIECE_SIZE][PIECE_SIZE];  
    int x, y;                           
    int type;                            
    char symbol;                         
};

struct GameState {
    int board[BOARD_HEIGHT][BOARD_WIDTH]; 
    Piece currentPiece;                     
    Piece nextPiece; 
    int score;                              
    int level;                              
    int linesCleared;                       
    int baseSpeed;                          
    int currentSpeed;                      
    bool gameOver;                                         
};

#endif