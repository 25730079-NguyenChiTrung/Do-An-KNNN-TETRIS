#include "board.h"

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

bool coTheDatKhoi(
    const TrangThai &tt,
    const Khoi &khoi,
    int viTriMoiX,
    int viTriMoiY
) {
    for (int i = 0; i < KICH_THUOC_KHOI; i++) {
        for (int j = 0; j < KICH_THUOC_KHOI; j++) {
            if (khoi.hinh[i][j] == 1) {
                int x = viTriMoiX + j;
                int y = viTriMoiY + i;

                if (x < 0 || x >= CHIEU_RONG_BANG) return false;
                if (y < 0 || y >= CHIEU_CAO_BANG)  return false;

                if (tt.bang[y][x] != 0) return false;
            }
        }
    }
    return true;
}

void datKhoiVaoBang(TrangThai &tt) {
    for (int i = 0; i < KICH_THUOC_KHOI; i++) {
        for (int j = 0; j < KICH_THUOC_KHOI; j++) {
            if (tt.khoiHienTai.hinh[i][j] == 1) {
                int x = tt.khoiHienTai.viTriX + j;
                int y = tt.khoiHienTai.viTriY + i;

                if (x >= 0 && x < CHIEU_RONG_BANG &&
                    y >= 0 && y < CHIEU_CAO_BANG) {
                    tt.bang[y][x] = tt.khoiHienTai.loai + 1;
                }
            }
        }
    }
}

int xoaHangDay(TrangThai &tt) {
    int dem = 0;

    for (int i = CHIEU_CAO_BANG - 1; i >= 0; i--) {
        bool day = true;

        for (int j = 0; j < CHIEU_RONG_BANG; j++) {
            if (tt.bang[i][j] == 0) {
                day = false;
                break;
            }
        }

        if (day) {
            dem++;

            for (int k = i; k > 0; k--) {
                for (int j = 0; j < CHIEU_RONG_BANG; j++) {
                    tt.bang[k][j] = tt.bang[k - 1][j];
                }
            }

            for (int j = 0; j < CHIEU_RONG_BANG; j++) {
                tt.bang[0][j] = 0;
            }

            i++; // kiem tra lai hang nay
        }
    }

    return dem;
}

void capNhatDiemVaTocDo(TrangThai &tt, int soHangXoa) {
    
}