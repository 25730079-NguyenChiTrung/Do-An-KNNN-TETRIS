/*
 * THANH VIEN 3: QUAN LY BANG CHOI
 * File: board.cpp
 */
 #include "bangchoi.h"
 void khoiTaoBang(TrangThai &tt) {
    for (int i = 0; i < CHIEU_CAO_BANG; i++) {
        for (int j = 0; j < CHIEU_RONG_BANG; j++) {
            tt.bang[i][j] = 0;
        }
    }

    tt.diem = 0;
    tt.capDo = 1;
    tt.soHangDaXoa = 0;
    tt.tocDoCoBan = 500;
    tt.tocDoHienTai = tt.tocDoCoBan;
    tt.ketThuc = false;
}