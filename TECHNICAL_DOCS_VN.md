# TÀI LIỆU KỸ THUẬT

## Trò Chơi Tetris Console - Tài Liệu Kỹ Thuật

### Mục Lục
1. Tổng Quan Kiến Trúc
2. Mô Tả Các Module
3. Cấu Trúc Dữ Liệu
4. Các Thuật Toán Cốt Lõi
5. Vòng Lặp Game
6. Tương Thích Đa Nền Tảng
7. Hệ Thống Build

---

## Tổng Quan Kiến Trúc

Trò chơi Tetris tuân theo **kiến trúc modular** với sự phân tách rõ ràng các thành phần:

```
┌─────────────────────────────────────────┐
│            main.cpp                      │
│         (Lớp Tích Hợp)                   │
└─────────────────────────────────────────┘
           │
           ├──────────────┬──────────────┬──────────────┬──────────────┐
           │              │              │              │              │
           ▼              ▼              ▼              ▼              ▼
    ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐
    │ structs.h│   │  piece   │   │  board   │   │ display  │   │  input   │
    │(Dữ liệu) │   │(Logic)   │   │(Logic)   │   │(Giao diện│   │(Điều khiển│
    └──────────┘   └──────────┘   └──────────┘   └──────────┘   └──────────┘
```

**Mẫu Thiết Kế:** Codebase tuân theo phương pháp **lập trình thủ tục** với thiết kế modular, sử dụng:
- **Thiết Kế Hướng Dữ Liệu**: Trạng thái game được đóng gói trong các struct
- **Phân Tách Chức Năng**: Mỗi module xử lý một trách nhiệm cụ thể
- **Trừu Tượng Hóa Đa Nền Tảng**: Code đặc thù cho từng nền tảng được cô lập trong `input.cpp`

---

## Mô Tả Các Module

### 1. Lớp Dữ Liệu - `structs.h`

**Mục đích:** Định nghĩa tất cả cấu trúc dữ liệu và hằng số cho game.

**Các Hằng Số Chính:**
```cpp
BOARD_WIDTH = 10      // Chiều rộng bàn chơi Tetris chuẩn
BOARD_HEIGHT = 20     // Chiều cao bàn chơi Tetris chuẩn
PIECE_SIZE = 4        // Kích thước tối đa cho bất kỳ Tetromino nào
```

**Cấu Trúc Dữ Liệu:**

#### Struct `Piece`
Đại diện cho một mảnh Tetromino với:
- `shape[4][4]`: Ma trận 4×4 biểu diễn hình dạng mảnh (1 = có khối, 0 = trống)
- `x, y`: Vị trí trên bàn chơi (góc trên bên trái của hộp giới hạn)
- `type`: Số nguyên 0-6 đại diện cho loại mảnh (I, O, T, S, Z, J, L)
- `symbol`: Ký tự để hiển thị ('I', 'O', 'T', 'S', 'Z', 'J', 'L')

#### Struct `GameState`
Đóng gói toàn bộ trạng thái game:
- `board[20][10]`: Mảng 2D đại diện cho bàn chơi (0 = trống, 1+ = loại mảnh)
- `currentPiece`: Mảnh đang rơi hiện tại
- `nextPiece`: Xem trước mảnh tiếp theo
- `score`: Điểm số hiện tại của người chơi
- `level`: Cấp độ khó hiện tại
- `linesCleared`: Tổng số hàng đã xóa
- `baseSpeed`: Tốc độ rơi ban đầu (500ms)
- `currentSpeed`: Tốc độ rơi hiện tại (giảm theo cấp độ)
- `gameOver`: Cờ boolean cho trạng thái game

**Các Hình Dạng Tetromino:**
Mảng `SHAPES` định nghĩa 7 mảnh Tetris chuẩn sử dụng ma trận 4×4:
- **Mảnh I**: Đường thẳng (4 khối)
- **Mảnh O**: Hình vuông (2×2 khối)
- **Mảnh T**: Hình chữ T
- **Mảnh S**: Hình chữ S
- **Mảnh Z**: Hình chữ Z
- **Mảnh J**: Hình chữ J
- **Mảnh L**: Hình chữ L

---

### 2. Logic Mảnh Ghép - `piece.h` / `piece.cpp`

**Mục đích:** Xử lý tất cả các thao tác với mảnh Tetromino.

#### Các Hàm:

##### `createPiece()` → `Piece`
**Thuật toán:**
1. Sinh ngẫu nhiên loại (0-6)
2. Sao chép hình dạng tương ứng từ mảng `SHAPES`
3. Đặt vị trí ban đầu (giữa-trên cùng của bàn chơi)
4. Gán ký hiệu hiển thị

```cpp
Piece p;
p.type = rand() % 7;
p.x = BOARD_WIDTH / 2 - 2;  // Căn giữa theo chiều ngang
p.y = 0;                     // Đỉnh bàn chơi
```

##### `canPlace(GameState &game, Piece &piece, int newX, int newY)` → `bool`
**Thuật Toán Phát Hiện Va Chạm:**
1. Duyệt qua hộp giới hạn 4×4 của mảnh
2. Với mỗi ô có khối (shape[i][j] == 1):
   - Tính tọa độ bàn chơi: `boardX = newX + j`, `boardY = newY + i`
   - Kiểm tra nếu ra ngoài giới hạn: `boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT`
   - Kiểm tra nếu trùng với mảnh đã có: `board[boardY][boardX] != 0`
3. Trả về false nếu phát hiện va chạm, ngược lại trả về true

**Độ Phức Tạp Thời Gian:** O(16) = O(1) (luôn kiểm tra ma trận 4×4)

##### `rotatePiece(GameState &game)`
**Thuật Toán Xoay (90° Theo Chiều Kim Đồng Hồ):**
```
Phép biến đổi ma trận:
shape'[i][j] = shape[SIZE-1-j][i]

Ví dụ (mảnh T):
Trước:         Sau:
. # # #        . . #
. . # .   →    . # #
. . . .        . . #
. . . .        . . .
```

1. Tạo mảnh tạm đã xoay
2. Áp dụng phép biến đổi ma trận
3. Kiểm tra vị trí với `canPlace()`
4. Áp dụng xoay nếu hợp lệ, ngược lại giữ hướng ban đầu

##### `moveLeft()`, `moveRight()`, `moveDown()`
**Thuật Toán Di Chuyển:**
1. Tính vị trí mới (x±1 hoặc y+1)
2. Kiểm tra với `canPlace()`
3. Cập nhật vị trí nếu hợp lệ
4. Trả về false nếu không thể di chuyển xuống (cho `moveDown()`)

---

### 3. Logic Bàn Chơi - `board.h` / `board.cpp`

**Mục đích:** Quản lý trạng thái bàn chơi, xóa hàng và tính điểm.

#### Các Hàm:

##### `initBoard(GameState &game)`
Khởi tạo trạng thái game:
- Xóa mảng bàn chơi (tất cả về không)
- Đặt score = 0, level = 1, linesCleared = 0
- Đặt baseSpeed = 500ms, currentSpeed = 500ms
- Đặt gameOver = false

##### `placePiece(GameState &game)`
**Thuật toán:**
1. Duyệt qua hình dạng 4×4 của mảnh hiện tại
2. Với mỗi ô có khối, ghi loại mảnh vào bàn chơi tại vị trí đó
3. Lưu loại mảnh + 1 (để 0 vẫn là trống, 1-7 là các loại mảnh)

##### `removeLines(GameState &game)` → `int`
**Thuật Toán Xóa Hàng:**
```
1. Bắt đầu từ hàng dưới cùng (i = BOARD_HEIGHT - 1)
2. Với mỗi hàng:
   a. Kiểm tra nếu tất cả các ô khác không (hàng đầy)
   b. Nếu đầy:
      - Tăng bộ đếm linesRemoved
      - Dịch tất cả các hàng phía trên xuống một hàng
      - Xóa hàng trên cùng
      - Kiểm tra lại hàng hiện tại (i++) do các hàng đã dịch
3. Trả về tổng số hàng đã xóa
```

**Độ Phức Tạp Thời Gian:** O(H × W × H) = O(20 × 10 × 20) = O(4000) trường hợp xấu nhất

##### `updateScoreAndSpeed(GameState &game, int linesRemoved)`
**Hệ Thống Tính Điểm:**
```cpp
Tính điểm:
1 hàng:  100 × level
2 hàng:  300 × level
3 hàng:  500 × level
4 hàng:  800 × level
```

**Tăng Tốc Độ:**
```cpp
currentSpeed = baseSpeed - (level - 1) × 40
Tốc độ tối thiểu: 100ms
Tăng cấp: Mỗi 10 hàng đã xóa
```

**Ví dụ:**
- Cấp 1: 500ms
- Cấp 2: 460ms
- Cấp 3: 420ms
- Cấp 10: 140ms
- Cấp 11+: 100ms (giới hạn)

##### `spawnNewPiece(GameState &game)`
**Thuật toán:**
1. Chuyển `nextPiece` thành `currentPiece`
2. Sinh `nextPiece` mới với `createPiece()`
3. Kiểm tra nếu mảnh hiện tại có thể đặt tại vị trí spawn
4. Đặt `gameOver = true` nếu không thể đặt (bàn chơi đầy)

---

### 4. Lớp Hiển Thị - `display.h` / `display.cpp`

**Mục đích:** Xử lý tất cả đầu ra hình ảnh ra console.

#### Các Hàm:

##### `clearScreen()`
**Triển Khai Đặc Thù Nền Tảng:**
```cpp
#ifdef _WIN32
    system("cls");      // Windows
#else
    system("clear");    // Linux/Mac
#endif
```

##### `draw(GameState &game)`
**Thuật Toán Render:**

1. **Tạo Bộ Đệm Hiển Thị:**
   ```cpp
   char display[BOARD_HEIGHT][BOARD_WIDTH];
   ```

2. **Render Trạng Thái Bàn Chơi:**
   - Sao chép bàn chơi vào bộ đệm hiển thị
   - Ô trống → khoảng trắng ' '
   - Ô có khối → '#'

3. **Phủ Mảnh Hiện Tại:**
   - Duyệt qua hình dạng mảnh
   - Với các ô có khối, vẽ ký hiệu mảnh tại (piece.x + j, piece.y + i)

4. **Vẽ Giao Diện UI:**
   ```
   ╔══════════════════════════════════════╗
   ║         TRÒ CHƠI TETRIS CONSOLE      ║
   ╚══════════════════════════════════════╝
   
   +--------------------+     MẢNH KẾ TIẾP:
   |                    |     +--------+
   |   [bàn chơi]       |     | [next] |
   |                    |     +--------+
   +--------------------+     ĐIỂM: X
                              CẤP: X
                              HÀNG: X
   ```

5. **Hiển Thị Panel Bên:**
   - Xem trước mảnh tiếp theo (lưới 4×4)
   - Điểm số
   - Cấp độ
   - Số hàng đã xóa
   - Tốc độ hiện tại
   - Hướng dẫn điều khiển

##### `drawGameOver(GameState &game)`
Hiển thị thống kê cuối cùng:
- Điểm số cuối cùng
- Cấp độ cuối cùng
- Tổng số hàng đã xóa

---

### 5. Lớp Nhập Liệu - `input.h` / `input.cpp`

**Mục đích:** Xử lý nhập liệu đa nền tảng và các tiện ích thời gian.

#### Các Hàm:

##### `keyPressed()` → `bool`
**Phát Hiện Nhập Liệu Không Chặn:**

**Triển Khai Windows:**
```cpp
return _kbhit();  // Trả về true nếu có phím trong buffer
```

**Triển Khai Linux/Mac:**
```cpp
1. Lưu cài đặt terminal
2. Đặt terminal vào chế độ non-canonical (không đệm dòng)
3. Tắt echo
4. Đặt file descriptor không chặn
5. Thử đọc một ký tự
6. Khôi phục cài đặt terminal
7. Trả về true nếu có ký tự
```

**Độ Phức Tạp Thời Gian:** O(1)

##### `getKey()` → `char`
**Đọc Nhập Liệu Chặn:**

**Windows:**
```cpp
return _getch();  // Đọc ký tự không có echo
```

**Linux/Mac:**
```cpp
1. Đặt terminal vào chế độ raw (không đệm, không echo)
2. Đọc một ký tự với getchar()
3. Khôi phục cài đặt terminal
4. Trả về ký tự
```

##### `sleepMs(int ms)`
**Sleep Đặc Thù Nền Tảng:**
```cpp
#ifdef _WIN32
    Sleep(ms);           // Windows: mili giây
#else
    usleep(ms * 1000);   // Linux/Mac: micro giây
#endif
```

##### `getCurrentTimeMs()` → `long long`
**Đo Thời Gian Độ Phân Giải Cao:**

**Windows:**
```cpp
return GetTickCount();  // Thời gian hoạt động hệ thống tính bằng ms
```

**Linux/Mac:**
```cpp
struct timeval tv;
gettimeofday(&tv, NULL);
return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
```

---

## Các Thuật Toán Cốt Lõi

### Phát Hiện Va Chạm
**Hàm:** `canPlace()`

**Mã giả:**
```
function canPlace(game, piece, newX, newY):
    for i in 0 to PIECE_SIZE-1:
        for j in 0 to PIECE_SIZE-1:
            if piece.shape[i][j] == 1:
                boardX = newX + j
                boardY = newY + i
                
                if boardX < 0 or boardX >= BOARD_WIDTH:
                    return false
                if boardY < 0 or boardY >= BOARD_HEIGHT:
                    return false
                if game.board[boardY][boardX] != 0:
                    return false
    
    return true
```

### Xóa Hàng
**Hàm:** `removeLines()`

**Mã giả:**
```
function removeLines(game):
    linesRemoved = 0
    
    for i from BOARD_HEIGHT-1 down to 0:
        fullLine = true
        
        for j in 0 to BOARD_WIDTH-1:
            if game.board[i][j] == 0:
                fullLine = false
                break
        
        if fullLine:
            linesRemoved++
            
            // Dịch các hàng xuống
            for k from i down to 1:
                for j in 0 to BOARD_WIDTH-1:
                    game.board[k][j] = game.board[k-1][j]
            
            // Xóa hàng trên cùng
            for j in 0 to BOARD_WIDTH-1:
                game.board[0][j] = 0
            
            i++  // Kiểm tra lại hàng hiện tại
    
    return linesRemoved
```

### Xoay Mảnh
**Hàm:** `rotatePiece()`

**Phép Biến Đổi Ma Trận:**
```
Công thức xoay (90° theo chiều kim đồng hồ):
    rotated[i][j] = original[SIZE-1-j][i]

Ví dụ trực quan:
    0 1 2 3         3 2 1 0
    . # # #         . . # .
    . . # .    →    . # # .
    . . . .         . . # .
    . . . .         . . # .
    
Ánh xạ chỉ số:
    [0,1] → [1,3]
    [0,2] → [2,3]
    [0,3] → [3,3]
    [1,2] → [2,2]
```

---

## Vòng Lặp Game

**Hàm:** `gameLoop()` trong `main.cpp`

**Thuật Toán Vòng Lặp Chính:**

```
Khởi tạo lastFallTime = getCurrentTimeMs()

while not game.gameOver:
    // 1. Render
    draw(game)
    
    // 2. Xử Lý Nhập Liệu (không chặn)
    if keyPressed():
        key = getKey()
        
        switch key:
            'a'/'A': moveLeft(game)
            'd'/'D': moveRight(game)
            'w'/'W': rotatePiece(game)
            's'/'S': 
                if moveDown(game):
                    score += 1  // Điểm thưởng soft drop
            ' ':     hardDrop(game)
            'q'/'Q': gameOver = true
    
    // 3. Rơi Tự Động
    currentTime = getCurrentTimeMs()
    if currentTime - lastFallTime >= currentSpeed:
        if not moveDown(game):
            // Mảnh đã chạm đáy
            placePiece(game)
            lines = removeLines(game)
            updateScoreAndSpeed(game, lines)
            spawnNewPiece(game)
        
        lastFallTime = currentTime
    
    // 4. Điều Khiển Tốc Độ Khung Hình
    sleepMs(30)  // ~33 FPS
```

**Sơ Đồ Thời Gian:**
```
Thời gian (ms): 0      30     60     90     120    ...    500
                |      |      |      |      |      |      |
Kiểm tra       ─┐    ─┐    ─┐    ─┐    ─┐    ─┐    ─┐
Input:          └─────└─────└─────└─────└─────└─────└──

Render:      ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

Rơi Tự Động: ─────────────────────────────────────┐
(500ms)                                            └── Rơi!
```

**Thuật Toán Hard Drop:**
```cpp
function hardDrop(game):
    while moveDown(game):
        score += 2  // Điểm thưởng hard drop
    // Mảnh tự động được đặt sau vòng lặp
```

---

## Tương Thích Đa Nền Tảng

### Chỉ Thị Tiền Xử Lý
Codebase sử dụng biên dịch có điều kiện:

```cpp
#ifdef _WIN32
    // Code đặc thù cho Windows
#else
    // Code đặc thù cho Linux/Mac
#endif
```

### Sự Khác Biệt Giữa Các Nền Tảng

| Tính Năng | Windows | Linux/Mac |
|-----------|---------|-----------|
| **Phát Hiện Input** | `_kbhit()` từ `<conio.h>` | Cờ Terminal + `fcntl()` |
| **Đọc Ký Tự** | `_getch()` từ `<conio.h>` | `getchar()` với termios |
| **Sleep** | `Sleep(ms)` từ `<windows.h>` | `usleep(us)` từ `<unistd.h>` |
| **Đo Thời Gian** | `GetTickCount()` | `gettimeofday()` |
| **Xóa Màn Hình** | `system("cls")` | `system("clear")` |

### Cấu Hình Terminal (Unix)

**Chế Độ Non-Canonical:**
```cpp
struct termios newt;
newt.c_lflag &= ~(ICANON | ECHO);  // Tắt đệm dòng và echo
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
```

**I/O Không Chặn:**
```cpp
int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
```

---

## Hệ Thống Build

### Windows - `build.bat` / `run.bat`

**Lệnh Build:**
```batch
g++ -std=c++17 -Wall -o tetris.exe main.cpp piece.cpp board.cpp display.cpp input.cpp
```

**Các Cờ:**
- `-std=c++17`: Sử dụng chuẩn C++17
- `-Wall`: Bật tất cả cảnh báo
- `-o tetris.exe`: Tên file thực thi đầu ra

### Linux/Mac - `Makefile`

**Các Target Make:**
```makefile
all:        # Build tất cả file thực thi
run-main:   # Build và chạy file thực thi chính
clean:      # Xóa thư mục build
list:       # Liệt kê các file thực thi có sẵn
```

**Quy Trình Build:**
1. Biên dịch các nguồn không phải main thành file object (`.o`)
2. Liên kết nguồn main với các file object để tạo file thực thi

**Ví dụ:**
```bash
make             # Biên dịch
make run-main    # Biên dịch và chạy
make clean       # Xóa các file build
```

---

## Các Cân Nhắc Về Hiệu Năng

### Phân Tích Độ Phức Tạp Thời Gian

| Hàm | Độ Phức Tạp | Ghi Chú |
|----------|------------|-------|
| `createPiece()` | O(16) = O(1) | Sao chép ma trận 4×4 cố định |
| `canPlace()` | O(16) = O(1) | Kiểm tra ma trận 4×4 cố định |
| `rotatePiece()` | O(16) = O(1) | Biến đổi ma trận cố định |
| `placePiece()` | O(16) = O(1) | Ghi ma trận 4×4 cố định |
| `removeLines()` | O(H²×W) | Xấu nhất: 20×20×10 = 4000 phép toán |
| `draw()` | O(H×W) | 20×10 = 200 ô |

### Độ Phức Tạp Không Gian

| Cấu Trúc | Kích Thước | Ghi Chú |
|-----------|------|-------|
| `GameState` | ~800 bytes | Board: 20×10×4 = 800 bytes |
| `Piece` | ~80 bytes | Shape: 4×4×4 = 64 bytes + metadata |
| Bộ đệm hiển thị | 400 bytes | 20×10×2 = 400 bytes (mảng char) |

**Tổng Bộ Nhớ:** < 2 KB

### Tốc Độ Khung Hình
- Mục tiêu: ~33 FPS (độ trễ 30ms)
- Kiểm tra input: Mỗi khung hình
- Render: Mỗi khung hình
- Bộ đếm thời gian rơi: Biến đổi (100-500ms)

---

## Xử Lý Lỗi

### Phát Hiện Game Over
**Điều kiện:** Mảnh mới không thể đặt tại vị trí spawn
```cpp
if (!canPlace(game, game.currentPiece, game.currentPiece.x, game.currentPiece.y)) {
    game.gameOver = true;
}
```

### Kiểm Tra Giới Hạn
Tất cả các hàm di chuyển sử dụng `canPlace()` để xác thực:
- Giới hạn bàn chơi (0 ≤ x < 10, 0 ≤ y < 20)
- Va chạm với các mảnh đã có

### Xoay Không Hợp Lệ
Nếu xoay gây ra va chạm, giữ nguyên hướng ban đầu:
```cpp
if (canPlace(game, rotated, rotated.x, rotated.y)) {
    game.currentPiece = rotated;  // Áp dụng xoay
}
// ngược lại: bỏ qua xoay
```

---

## Các Cải Tiến Tương Lai

### Các Cải Tiến Tiềm Năng
1. **Wall Kicks:** Cho phép xoay gần tường với điều chỉnh vị trí
2. **Ghost Piece:** Hiển thị nơi mảnh sẽ rơi xuống
3. **Hold Piece:** Khả năng lưu một mảnh để dùng sau
4. **Phát Hiện T-Spin:** Điểm thưởng cho nước đi nâng cao
5. **Hỗ Trợ Màu Sắc:** Mã màu ANSI cho các mảnh khác nhau
6. **Điểm Cao:** Lưu trữ lâu dài điểm số cao nhất
7. **Chế Độ Khó:** Cài đặt sẵn Dễ/Bình Thường/Khó
8. **Hiệu Ứng Âm Thanh:** Tiếng beep terminal cho các sự kiện

### Khả Năng Mở Rộng
Thiết kế modular cho phép dễ dàng thêm:
- Các loại mảnh mới (sửa đổi mảng `SHAPES`)
- Hệ thống tính điểm tùy chỉnh (sửa đổi `updateScoreAndSpeed()`)
- Kích thước bàn chơi khác nhau (thay đổi `BOARD_WIDTH`/`BOARD_HEIGHT`)
- Điều khiển thay thế (sửa đổi xử lý input trong `main.cpp`)

---

## Tài Liệu Tham Khảo

- **Tetris Guideline:** Quy tắc và thông số kỹ thuật chính thức
- **Tetromino Wiki:** Hình dạng mảnh và hệ thống xoay
- **SRS (Super Rotation System):** Thuật toán xoay nâng cao (chưa triển khai)

---

**Phiên Bản Tài Liệu:** 1.0  
**Cập Nhật Lần Cuối:** Tháng 12 năm 2025  
**Codebase:** Do-An-KNNN-TETRIS
