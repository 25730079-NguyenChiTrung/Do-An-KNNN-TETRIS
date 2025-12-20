/*
 * THANH VIEN 5: XU LY INPUT & TICH HOP
 * File: input.h
 * 
 * Nhiem vu:
 * - Doc phim tu ban phim (non-blocking)
 * - Ham sleep va lay thoi gian
 * - Ho tro ca Windows va Mac/Linux
*/

#ifndef INPUT_H
#define INPUT_H

/*
 * Kiem tra xem co phim nao duoc nhan khong
 */
bool keyPressed();

/*
 * Doc phim da duoc nhan
 */
char getKey();

/*
 * Tam dung chuong trinh trong mot khoang thoi gian
 */
void sleepMs(int ms);

/*
 * Dung de tinh thoi gian (ms) giua cac lan khoi roi xuong
 */
long long getCurrentTimeMs();
#endif