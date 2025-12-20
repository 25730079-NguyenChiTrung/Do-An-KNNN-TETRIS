/*
 * THANH VIEN 5: VONG LAP GAME CHINH & TICH HOP
 * File: main.cpp
 * 
 * Day la file chinh cua chuong trinh
 * Tich hop tat ca cac module tu cac thanh vien khac
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "structs.h"
#include "input.h"

void gameLoop(GameState &game) {
  // Khoi tao Mock trang thai game
  game.score = 0;
  game.level = 1;
  game.linesCleared = 0;
  game.baseSpeed = 500;
  game.currentSpeed = game.baseSpeed;
  game.gameOver = false;


  while (!game.gameOver) {
    if (keyPressed()) {
      char key = getKey();
      std::cout << "Phim da nhan: " << key << std::endl;
    }
  }
}


int main() {

  GameState game;

  gameLoop(game);

  getKey();

  return 0;
}