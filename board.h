/*
 * THANH VIEN 3: QUAN LY BANG CHOI
 * File: board.h
 * 
 * Nhiem vu:
 * - Khoi tao game
 * - Dat khoi vao bang
 * - Xoa hang day (QUAN TRONG!)
 * - Cap nhat diem va toc do
*/
#ifndef BANGCHOI_H
#define BANGCHOI_H


const int CHIEU_RONG_BANG = 10;
const int CHIEU_CAO_BANG  = 20;
const int KICH_THUOC_KHOI = 4;

struct Khoi {
    int hinh[KICH_THUOC_KHOI][KICH_THUOC_KHOI];
    int viTriX;
    int viTriY;
    int loai;
    char kyTu;
};

struct TrangThai {
    int bang[CHIEU_CAO_BANG][CHIEU_RONG_BANG];
    Khoi khoiHienTai;
    int diem;
    int capDo;
    int soHangDaXoa;
    int tocDoCoBan;
    int tocDoHienTai;
    bool ketThuc;
};