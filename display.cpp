/*
 * THANH VIEN 4: HIEN THI GIAO DIEN
 * File: display.cpp
 */

#include "display.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void xoaManHinh()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void ve(GameState &game)
{
	xoaManHinh();

	char display[BOARD_HEIGHT][BOARD_WIDTH];

	for (int i = 0; i < BOARD_HEIGHT; ++i)
	{
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			if (game.board[i][j] == 0) {
				display[i][j] = '.';
			} else {
				display[i][j] = '#';
			}
		}
	}
	
}