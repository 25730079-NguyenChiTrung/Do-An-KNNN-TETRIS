/*
 * THANH VIEN 5: XU LY INPUT & TICH HOP
 * File: input.cpp
 * 
 * LUU Y: File nay can xu ly cho ca Windows va Mac/Linux
 * Su dung #ifdef _WIN32 de phan biet he dieu hanh
*/

#include "input.h"

#include <termios.h>    // Thay doi che do terminal
#include <unistd.h>     // usleep()
#include <fcntl.h>      // fcntl() - file control
#include <cstdio>       // getchar(), ungetc()

bool keyPressed() {
  #ifdef _WIN32
    return _kbhit();
  #else
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
      ungetc(ch, stdin);
      return true;
    }
    return false;
  #endif
}