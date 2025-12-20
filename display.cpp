/*
 * THANH VIEN 4: HIEN THI GIAO DIEN
 * File: display.cpp
*/

#include "display.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void xoaManHinh() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}