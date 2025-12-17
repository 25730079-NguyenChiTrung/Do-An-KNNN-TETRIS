/*
 * THANH VIEN 2: XU LY KHOI TETRIS
 * File: piece.cpp
 */
#include "piece.h"
#include <cstdlib>
#include <ctime>

const int SHAPES[7][PIECE_SIZE][PIECE_SIZE] = {
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
    {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}};

const char PIECE_SYMBOLS[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

Piece createPiece()
{
    Piece p;
    p.type = rand() % 7;
    p.symbol = PIECE_SYMBOLS[p.type];
    p.x = BOARD_WIDTH / 2 - 2;
    p.y = 0;

    for (int i = 0; i < PIECE_SIZE; i++)
    {
        for (int j = 0; j < PIECE_SIZE; j++)
        {
            p.shape[i][j] = SHAPES[p.type][i][j];
        }
    }
    return p;
}

bool canPlace(GameState &game, Piece &piece, int newX, int newY)
{
    for (int i = 0; i < PIECE_SIZE; i++)
    {
        for (int j = 0; j < PIECE_SIZE; j++)
        {
            if (piece.shape[i][j] == 1)
            {
                int bx = newX + j;
                int by = newY + i;

                if (bx < 0 || bx >= BOARD_WIDTH)
                    return false;
                if (by < 0 || by >= BOARD_HEIGHT)
                    return false;

                if (game.board[by][bx] != 0)
                    return false;
            }
        }
    }
    return true;
}

void rotatePiece(GameState &game)
{
    Piece rotated = game.currentPiece;

    for (int i = 0; i < PIECE_SIZE; i++)
    {
        for (int j = 0; j < PIECE_SIZE; j++)
        {
            rotated.shape[i][j] = game.currentPiece.shape[PIECE_SIZE - 1 - j][i];
        }
    }

    if (canPlace(game, rotated, rotated.x, rotated.y))
    {
        game.currentPiece = rotated;
    }
}

void moveLeft(GameState &game)
{
    if (canPlace(game, game.currentPiece, game.currentPiece.x - 1, game.currentPiece.y))
    {
        game.currentPiece.x--;
    }
}

void moveRight(GameState &game)
{
    if (canPlace(game, game.currentPiece, game.currentPiece.x + 1, game.currentPiece.y))
    {
        game.currentPiece.x++;
    }
}

bool moveDown(GameState &game)
{
    if (canPlace(game, game.currentPiece, game.currentPiece.x, game.currentPiece.y + 1))
    {
        game.currentPiece.y++;
        return true;
    }
    return false;
}