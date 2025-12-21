/*
 * THANH VIEN 3: XU LY BANG CHOI
 * File: board.h
 *
 * Nhiem vu:
 * - Khoi tao bang choi
 * - Dat khoi vao bang
 * - Xoa cac hang da day
 * - Cap nhat diem va toc do
 */

#ifndef BOARD_H
#define BOARD_H

#include "structs.h"

// Khoi tao bang choi (xoa toan bo bang)
void initBoard(GameState &game);

// Dat khoi hien tai vao bang
void placePiece(GameState &game);

// Xoa cac hang da day va tra ve so hang da xoa
int removeLines(GameState &game);

// Cap nhat diem va toc do sau khi xoa hang
void updateScoreAndSpeed(GameState &game, int linesRemoved);

// Sinh khoi moi
void spawnNewPiece(GameState &game);

#endif
