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
