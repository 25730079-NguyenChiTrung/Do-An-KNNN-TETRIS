# TETRIS CONSOLE GAME

Game xếp hình Tetris chạy trên console, được viết bằng C++ sử dụng struct.

## Mô tả dự án

Đây là một phiên bản Tetris cổ điển chạy trên console/terminal, được thiết kế cho sinh viên đại học năm 2 làm đồ án Kỹ năng nghề nghiệp (KNNN). Game được phát triển theo mô hình modular với nhiều thành viên cùng tham gia.

## Phân công thành viên

### Thành viên 1 - Nguyễn Thị Thu Uyên: Cấu trúc dữ liệu & Hình dạng khối
**File:** `structs.h`
- Định nghĩa các hằng số game (BOARD_WIDTH, BOARD_HEIGHT, PIECE_SIZE)
- Tạo struct `Piece` (khối Tetris)
- Tạo struct `GameState` (trạng thái game)
- Định nghĩa 7 hình dạng khối Tetromino (I, O, T, S, Z, J, L)
- Định nghĩa ký tự hiển thị cho mỗi loại khối

### Thành viên 2 - Nguyễn Đông Triều: Xử lý khối Tetris
**Files:** `piece.h`, `piece.cpp`
- Tạo khối mới ngẫu nhiên (`createPiece`)
- Kiểm tra va chạm (`canPlace`)
- Xoay khối 90 độ (`rotatePiece`)
- Di chuyển khối sang trái/phải (`moveLeft`, `moveRight`)
- Di chuyển khối xuống dưới (`moveDown`)

### Thành viên 3 - Nguyễn Đức Trung: Xử lý bảng chơi
**Files:** `board.h`, `board.cpp`
- Khởi tạo bảng chơi (`initBoard`)
- Đặt khối vào bảng (`placePiece`)
- Xóa các hàng đã đầy (`removeLines`)
- Cập nhật điểm và tốc độ (`updateScoreAndSpeed`)
- Sinh khối mới (`spawnNewPiece`)

### Thành viên 4 - Nguyễn Quốc Trung: Hiển thị giao diện
**Files:** `display.h`, `display.cpp`
- Xóa màn hình console (`xoaManHinh`)
- Vẽ toàn bộ màn hình game (`ve`)
- Vẽ màn hình kết thúc game (`veGameOver`)
- Hiển thị bảng chơi, khối tiếp theo, điểm số, level, tốc độ
- Hiển thị hướng dẫn điều khiển

### Thành viên 5 - Nguyễn Chí Trung: Xử lý Input & Tích hợp
**Files:** `input.h`, `input.cpp`, `main.cpp`
- Kiểm tra phím bấm không chặn (`keyPressed`)
- Đọc phím đã bấm (`getKey`)
- Tạm dừng chương trình (`sleepMs`)
- Lấy thời gian hiện tại (`getCurrentTimeMs`)
- Hỗ trợ đa nền tảng (Windows và Mac/Linux)
- Tích hợp tất cả module trong `main.cpp`
- Vòng lặp game chính (`gameLoop`)

## Cấu trúc thư mục

```
Do-An-KNNN-TETRIS/
├── structs.h           # Cấu trúc dữ liệu và hình dạng khối
├── piece.h             # Header xử lý khối Tetris
├── piece.cpp           # Implementation xử lý khối
├── board.h             # Header xử lý bảng chơi
├── board.cpp           # Implementation xử lý bảng
├── display.h           # Header hiển thị giao diện
├── display.cpp         # Implementation hiển thị
├── input.h             # Header xử lý input
├── input.cpp           # Implementation xử lý input
├── main.cpp            # File chính, tích hợp toàn bộ
├── Makefile            # Build script cho Linux/Mac
├── build.bat           # Build script cho Windows
├── run.bat             # Build và chạy game cho Windows
└── README.md           # Tài liệu hướng dẫn
```

## Yêu cầu hệ thống

- **Compiler:** g++ với hỗ trợ C++17
- **Hệ điều hành:** Windows, Linux, hoặc macOS
- **Terminal:** Console/Terminal hỗ trợ Unicode (để hiển thị ký tự đặc biệt)

## Hướng dẫn biên dịch và chạy

### Trên Windows (PowerShell/CMD)

#### Cách 1: Sử dụng build script
```bash
# Chỉ biên dịch
.\build.bat

# Biên dịch và chạy luôn
.\run.bat
```

#### Cách 2: Biên dịch thủ công
```bash
# Biên dịch
g++ -std=c++17 -Wall -o tetris.exe main.cpp piece.cpp board.cpp display.cpp input.cpp

# Chạy game
.\tetris.exe
```

### Trên Linux/Mac

#### Cách 1: Sử dụng Makefile
```bash
# Biên dịch
make

# Chạy game
make run-main
```

#### Cách 2: Biên dịch thủ công
```bash
# Biên dịch
g++ -std=c++17 -Wall -o tetris main.cpp piece.cpp board.cpp display.cpp input.cpp

# Chạy game
./tetris
```

## Hướng dẫn chơi

### Điều khiển

| Phím | Chức năng |
|------|-----------|
| **A** hoặc **←** | Di chuyển khối sang trái |
| **D** hoặc **→** | Di chuyển khối sang phải |
| **W** hoặc **↑** | Xoay khối 90° theo chiều kim đồng hồ |
| **S** hoặc **↓** | Soft Drop (rơi nhanh hơn, +1 điểm) |
| **SPACE** | Hard Drop (rơi ngay xuống đáy, +2 điểm mỗi ô) |
| **Q** | Thoát game |

### Quy tắc chơi

1. **Mục tiêu:** Xếp các khối Tetromino rơi xuống để tạo thành các hàng ngang hoàn chỉnh
2. **Xóa hàng:** Khi một hàng được lấp đầy hoàn toàn, nó sẽ bị xóa và bạn nhận được điểm
3. **Tăng level:** Mỗi 10 hàng được xóa, bạn sẽ lên 1 level
4. **Tăng tốc độ:** Mỗi level, tốc độ khối rơi sẽ tăng lên (giảm 40ms mỗi level)
5. **Game Over:** Khi khối mới không thể xuất hiện (bảng đã đầy)

### Tính điểm

- **1 hàng:** 100 điểm × Level
- **2 hàng:** 300 điểm × Level
- **3 hàng:** 500 điểm × Level
- **4 hàng:** 800 điểm × Level
- **Soft Drop:** +1 điểm mỗi ô
- **Hard Drop:** +2 điểm mỗi ô

### Các khối Tetromino

Game có 7 loại khối khác nhau:

- **I** - Thanh dài (4 ô)
- **O** - Hình vuông (2×2)
- **T** - Hình chữ T
- **S** - Hình chữ S
- **Z** - Hình chữ Z
- **J** - Hình chữ J
- **L** - Hình chữ L

## Tính năng

- ✅ 7 loại khối Tetromino cổ điển
- ✅ Xoay khối 90 độ
- ✅ Soft drop và Hard drop
- ✅ Hệ thống tính điểm
- ✅ Tăng level và tốc độ tự động
- ✅ Hiển thị khối tiếp theo
- ✅ Hiển thị điểm, level, số hàng đã xóa
- ✅ Hỗ trợ đa nền tảng (Windows, Linux, Mac)
- ✅ Điều khiển bằng phím mũi tên hoặc WASD
- ✅ Game Over detection

## Ghi chú kỹ thuật

### Cross-platform Support

Code sử dụng preprocessor directives để hỗ trợ nhiều nền tảng:

- **Windows:** Sử dụng `<conio.h>` và `<windows.h>` cho `_kbhit()`, `_getch()`, `Sleep()`, `GetTickCount()`
- **Linux/Mac:** Sử dụng `<termios.h>`, `<fcntl.h>`, `<sys/time.h>` cho non-blocking input và timing

### Kiến trúc Modular

Project được tổ chức theo mô hình modular để dễ phân công công việc:

1. **Data Layer** (`structs.h`) - Định nghĩa dữ liệu
2. **Piece Logic** (`piece.h/cpp`) - Logic xử lý khối
3. **Board Logic** (`board.h/cpp`) - Logic xử lý bảng
4. **Display Layer** (`display.h/cpp`) - Tầng hiển thị
5. **Input Layer** (`input.h/cpp`) - Tầng nhập liệu
6. **Integration** (`main.cpp`) - Tích hợp và game loop

## Xử lý lỗi thường gặp

### Không biên dịch được

```
error: 'Sleep' was not declared in this scope
```
→ Đảm bảo bạn đang dùng g++ trên Windows hoặc có MinGW đã cài đặt

### Ký tự Unicode không hiển thị đúng

→ Sử dụng terminal hỗ trợ UTF-8 hoặc chạy:
```bash
chcp 65001  # Trên Windows
```

### Game chạy quá nhanh/chậm

→ Điều chỉnh `baseSpeed` trong hàm `initBoard()` ở `board.cpp` (mặc định: 500ms)

## Tác giả

Dự án đồ án Kỹ năng nghề nghiệp - Năm học 2024-2025 - Nhóm 7

## License

Dự án này được tạo ra cho mục đích học tập.

## Tham khảo

- [Tetris Guideline](https://tetris.wiki/Tetris_Guideline)
- [Tetromino Shapes](https://tetris.wiki/Tetromino)
