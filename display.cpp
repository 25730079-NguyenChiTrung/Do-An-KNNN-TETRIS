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
		for (int j = 0; j < BOARD_WIDTH; ++j)
		{
			if (game.board[i][j] == 0)
			{
				display[i][j] = '.';
			}
			else
			{
				display[i][j] = '#';
			}
		}
	}

	for (int i = 0; i < PIECE_SIZE; i++)
	{
		for (int j = 0; j < PIECE_SIZE; j++)
		{
			if (game.currentPiece.shape[i][j] == 1)
			{
				int boardX = game.currentPiece.x + j;
				int boardY = game.currentPiece.y + i;

				// Kiem tra trong pham vi
				if (boardY >= 0 && boardY < BOARD_HEIGHT &&
						boardX >= 0 && boardX < BOARD_WIDTH)
				{
					display[boardY][boardX] = game.currentPiece.symbol;
				}
			}
		}
	}

	cout << "\n";
	cout << "  ╔══════════════════════════════════════╗\n";
	cout << "  ║         TETRIS CONSOLE GAME          ║\n";
	cout << "  ╚══════════════════════════════════════╝\n\n";

	// In vien tren cua bang
	cout << "  +";
	for (int j = 0; j < BOARD_WIDTH * 2; j++)
		cout << "-";
	cout << "+     NEXT PIECE:\n";

	// In tung hang cua bang + thong tin ben phai
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		// In vien trai
		cout << "  |";

		// In noi dung hang
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (display[i][j] == ' ')
			{
				cout << "  "; // O trong (2 ky tu)
			}
			else
			{
				cout << display[i][j] << " "; // Khoi (ky tu + space)
			}
		}

		// In vien phai
		cout << "|";

		// Vi du:
		if (i == 1)
		{
			cout << "     +--------+";
		}
		else if (i >= 2 && i <= 5)
		{
			// TODO: Ve nextPiece
			cout << "     |";
			int row = i - 2;
			for (int j = 0; j < PIECE_SIZE; j++)
			{
				// TODO: Kiem tra va in nextPiece.shape[row][j]
				cout << "  "; // Tam thoi in trong
			}
			cout << "|";
		}
		else if (i == 6)
		{
			cout << "     +--------+";
		}
		else if (i == 8)
		{
			cout << "     SCORE: " << game.score;
		}
		else if (i == 10)
		{
			cout << "     LEVEL: " << game.level;
		}
		else if (i == 12)
		{
			cout << "     LINES: " << game.linesCleared;
		}
		else if (i == 14)
		{
			cout << "     SPEED: " << game.currentSpeed << "ms";
		}
		else if (i == 17)
		{
			cout << "     CONTROLS:";
		}
		else if (i == 18)
		{
			cout << "     A/D - Move";
		}
		else if (i == 19)
		{
			cout << "     W   - Rotate";
		}

		cout << "\n";
	}

	// In vien duoi cua bang + huong dan
	cout << "  +";
	for (int j = 0; j < BOARD_WIDTH * 2; j++)
		cout << "-";
	cout << "+     S   - Soft Drop\n";
	cout << "                               SPACE - Hard Drop\n";
	cout << "                               Q     - Quit\n";
}

void veGameOver(GameState &game)
{
	xoaManHinh();

	cout << "\n\n";
	cout << "  ╔══════════════════════════════════════╗\n";
	cout << "  ║            GAME OVER!                ║\n";
	cout << "  ╚══════════════════════════════════════╝\n\n";
}