/*
 * THANH VIEN 5: XU LY INPUT & TICH HOP
 * File: input.cpp
 * 
 * LUU Y: File nay can xu ly cho ca Windows va Mac/Linux
 * Su dung #ifdef _WIN32 de phan biet he dieu hanh
*/

#include "input.h"

// Thu vien cho Windows
#ifdef _WIN32
  #include <conio.h>      // _kbhit(), _getch()
  #include <windows.h>    // Sleep(), GetTickCount()
#else
// Thu vien cho Mac/Linux
  #include <termios.h>    // Thay doi che do terminal
  #include <unistd.h>     // STDIN_FILENO
  #include <fcntl.h>      // fcntl() - file control
  #include <sys/time.h>   // gettimeofday()
  #include <cstdio>       // getchar(), ungetc()
#endif

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

char getKey() {
  #ifdef _WIN32
    return _getch();
  #else
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
  #endif
}

void sleepMs(int ms) {
  #ifdef _WIN32
    // Windows
    Sleep(ms);
  #else
    // Mac/Linux
    usleep(ms * 1000);
  #endif
}

long long getCurrentTimeMs() {
  #ifdef _WIN32
    // Windows
    return GetTickCount();
  #else
      // Mac/Linux
      struct timeval tv;
      gettimeofday(&tv, NULL);
      return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
  #endif
}