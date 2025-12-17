/*
 * THANH VIEN 2: XU LY KHOI TETRIS
 * File: piece.h
 *
 * Nhiem vu:
 * - Tao khoi moi ngau nhien
 * - Kiem tra va cham
 * - Xoay khoi
 * - Di chuyen khoi
 */

#ifndef PIECE_H
#define PIECE_H

#include "structs.h"

Piece createPiece();
bool canPlace(GameState &game, Piece &piece, int newX, int newY);
void rotatePiece(GameState &game);
void moveLeft(GameState &game);
void moveRight(GameState &game);
bool moveDown(GameState &game);

#endif