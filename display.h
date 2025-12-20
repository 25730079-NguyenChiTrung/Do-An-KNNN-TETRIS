/*
 * THANH VIEN 4: HIEN THI GIAO DIEN
 * File: display.h
 * 
 * Nhiem vu:
 * - Xoa man hinh console
 * - Ve bang choi va khoi dang roi
 * - Hien thi thong tin game (score, level, next piece)
 * - Ve man hinh Game Over
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include "structs.h"

void xoaManHinh();

void ve(GameState &game);

void veGameOver(GameState &game);

#endif