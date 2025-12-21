# TECHNICAL_DOCS.MD

## Tetris Console Game - Technical Documentation

### Table of Contents
1. Architecture Overview
2. Module Descriptions
3. Data Structures
4. Core Algorithms
5. Game Loop
6. Cross-Platform Compatibility
7. Build System

---

## Architecture Overview

The Tetris game follows a **modular architecture** with clear separation of concerns:

```
┌─────────────────────────────────────────┐
│            main.cpp                      │
│         (Integration Layer)              │
└─────────────────────────────────────────┘
           │
           ├──────────────┬──────────────┬──────────────┬──────────────┐
           │              │              │              │              │
           ▼              ▼              ▼              ▼              ▼
    ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐
    │ structs.h│   │ piece    │   │  board   │   │ display  │   │  input   │
    │  (Data)  │   │ (Logic)  │   │ (Logic)  │   │  (View)  │   │(Control) │
    └──────────┘   └──────────┘   └──────────┘   └──────────┘   └──────────┘
```

**Design Pattern:** The codebase follows a **procedural programming** approach with modular design, using:
- **Data-Driven Design**: Game state encapsulated in structs
- **Separation of Concerns**: Each module handles a specific responsibility
- **Cross-Platform Abstraction**: Platform-specific code isolated in `input.cpp`

---

## Module Descriptions

### 1. Data Layer - `structs.h`

**Purpose:** Defines all data structures and constants for the game.

**Key Constants:**
```cpp
BOARD_WIDTH = 10      // Standard Tetris board width
BOARD_HEIGHT = 20     // Standard Tetris board height
PIECE_SIZE = 4        // Maximum bounding box for any Tetromino
```

**Data Structures:**

#### `Piece` Struct
Represents a Tetromino piece with:
- `shape[4][4]`: 4×4 matrix representing the piece shape (1 = filled, 0 = empty)
- `x, y`: Position on the board (top-left corner of bounding box)
- `type`: Integer 0-6 representing piece type (I, O, T, S, Z, J, L)
- `symbol`: Character for display ('I', 'O', 'T', 'S', 'Z', 'J', 'L')

#### `GameState` Struct
Encapsulates all game state:
- `board[20][10]`: 2D array representing the game board (0 = empty, 1+ = piece type)
- `currentPiece`: The active falling piece
- `nextPiece`: Preview of the next piece
- `score`: Current player score
- `level`: Current difficulty level
- `linesCleared`: Total lines cleared
- `baseSpeed`: Initial fall speed (500ms)
- `currentSpeed`: Current fall speed (decreases with level)
- `gameOver`: Boolean flag for game state

**Tetromino Shapes:**
The `SHAPES` array defines 7 standard Tetris pieces using 4×4 matrices:
- **I-piece**: Straight line (4 blocks)
- **O-piece**: Square (2×2 blocks)
- **T-piece**: T-shape
- **S-piece**: S-shape
- **Z-piece**: Z-shape
- **J-piece**: J-shape
- **L-piece**: L-shape

---

### 2. Piece Logic - `piece.h` / `piece.cpp`

**Purpose:** Handles all Tetromino piece operations.

#### Functions:

##### `createPiece()` → `Piece`
**Algorithm:**
1. Generate random type (0-6)
2. Copy corresponding shape from `SHAPES` array
3. Set initial position (center-top of board)
4. Assign display symbol

```cpp
Piece p;
p.type = rand() % 7;
p.x = BOARD_WIDTH / 2 - 2;  // Center horizontally
p.y = 0;                     // Top of board
```

##### `canPlace(GameState &game, Piece &piece, int newX, int newY)` → `bool`
**Collision Detection Algorithm:**
1. Iterate through piece's 4×4 bounding box
2. For each filled cell (shape[i][j] == 1):
   - Calculate board coordinates: `boardX = newX + j`, `boardY = newY + i`
   - Check if out of bounds: `boardX < 0 || boardX >= BOARD_WIDTH || boardY < 0 || boardY >= BOARD_HEIGHT`
   - Check if overlaps existing piece: `board[boardY][boardX] != 0`
3. Return false if any collision detected, true otherwise

**Time Complexity:** O(16) = O(1) (always checks 4×4 matrix)

##### `rotatePiece(GameState &game)`
**Rotation Algorithm (90° Clockwise):**
```
Matrix transformation:
shape'[i][j] = shape[SIZE-1-j][i]

Example (T-piece):
Before:        After:
. # # #        . . #
. . # .   →    . # #
. . . .        . . #
. . . .        . . .
```

1. Create temporary rotated piece
2. Apply matrix transformation
3. Test placement with `canPlace()`
4. Apply rotation if valid, otherwise keep original orientation

##### `moveLeft()`, `moveRight()`, `moveDown()`
**Movement Algorithm:**
1. Calculate new position (x±1 or y+1)
2. Test with `canPlace()`
3. Update position if valid
4. Return false if cannot move down (for `moveDown()`)

---

### 3. Board Logic - `board.h` / `board.cpp`

**Purpose:** Manages the game board state, line clearing, and scoring.

#### Functions:

##### `initBoard(GameState &game)`
Initializes game state:
- Clears board array (all zeros)
- Sets score = 0, level = 1, linesCleared = 0
- Sets baseSpeed = 500ms, currentSpeed = 500ms
- Sets gameOver = false

##### `placePiece(GameState &game)`
**Algorithm:**
1. Iterate through current piece's 4×4 shape
2. For each filled cell, write piece type to board at position
3. Stores piece type + 1 (so 0 remains empty, 1-7 are piece types)

##### `removeLines(GameState &game)` → `int`
**Line Clearing Algorithm:**
```
1. Start from bottom row (i = BOARD_HEIGHT - 1)
2. For each row:
   a. Check if all cells are non-zero (full line)
   b. If full:
      - Increment linesRemoved counter
      - Shift all rows above down by one
      - Clear top row
      - Re-check current row (i++) since rows shifted
3. Return total lines removed
```

**Time Complexity:** O(H × W × H) = O(20 × 10 × 20) = O(4000) worst case

##### `updateScoreAndSpeed(GameState &game, int linesRemoved)`
**Scoring System:**
```cpp
Points calculation:
1 line:  100 × level
2 lines: 300 × level
3 lines: 500 × level
4 lines: 800 × level
```

**Speed Progression:**
```cpp
currentSpeed = baseSpeed - (level - 1) × 40
Minimum speed: 100ms
Level increase: Every 10 lines cleared
```

**Example:**
- Level 1: 500ms
- Level 2: 460ms
- Level 3: 420ms
- Level 10: 140ms
- Level 11+: 100ms (capped)

##### `spawnNewPiece(GameState &game)`
**Algorithm:**
1. Move `nextPiece` to `currentPiece`
2. Generate new `nextPiece` with `createPiece()`
3. Test if current piece can be placed at spawn position
4. Set `gameOver = true` if placement fails (board full)

---

### 4. Display Layer - `display.h` / `display.cpp`

**Purpose:** Handles all visual output to the console.

#### Functions:

##### `clearScreen()`
**Platform-Specific Implementation:**
```cpp
#ifdef _WIN32
    system("cls");      // Windows
#else
    system("clear");    // Linux/Mac
#endif
```

##### `draw(GameState &game)`
**Rendering Algorithm:**

1. **Create Display Buffer:**
   ```cpp
   char display[BOARD_HEIGHT][BOARD_WIDTH];
   ```

2. **Render Board State:**
   - Copy board to display buffer
   - Empty cells → space ' '
   - Filled cells → '#'

3. **Overlay Current Piece:**
   - Iterate through piece shape
   - For filled cells, draw piece symbol at (piece.x + j, piece.y + i)

4. **Draw UI Layout:**
   ```
   ╔══════════════════════════════════════╗
   ║         TETRIS CONSOLE GAME          ║
   ╚══════════════════════════════════════╝
   
   +--------------------+     NEXT PIECE:
   |                    |     +--------+
   |   [game board]     |     | [next] |
   |                    |     +--------+
   +--------------------+     SCORE: X
                              LEVEL: X
                              LINES: X
   ```

5. **Display Side Panel:**
   - Next piece preview (4×4 grid)
   - Score
   - Level
   - Lines cleared
   - Current speed
   - Controls reference

##### `drawGameOver(GameState &game)`
Displays final statistics:
- Final score
- Final level
- Total lines cleared

---

### 5. Input Layer - `input.h` / `input.cpp`

**Purpose:** Cross-platform input handling and timing utilities.

#### Functions:

##### `keyPressed()` → `bool`
**Non-Blocking Input Detection:**

**Windows Implementation:**
```cpp
return _kbhit();  // Returns true if key in buffer
```

**Linux/Mac Implementation:**
```cpp
1. Save terminal settings
2. Set terminal to non-canonical mode (no line buffering)
3. Disable echo
4. Set non-blocking file descriptor
5. Try to read one character
6. Restore terminal settings
7. Return true if character available
```

**Time Complexity:** O(1)

##### `getKey()` → `char`
**Blocking Input Read:**

**Windows:**
```cpp
return _getch();  // Read character without echo
```

**Linux/Mac:**
```cpp
1. Set terminal to raw mode (no buffering, no echo)
2. Read one character with getchar()
3. Restore terminal settings
4. Return character
```

##### `sleepMs(int ms)`
**Platform-Specific Sleep:**
```cpp
#ifdef _WIN32
    Sleep(ms);           // Windows: milliseconds
#else
    usleep(ms * 1000);   // Linux/Mac: microseconds
#endif
```

##### `getCurrentTimeMs()` → `long long`
**High-Resolution Timing:**

**Windows:**
```cpp
return GetTickCount();  // System uptime in ms
```

**Linux/Mac:**
```cpp
struct timeval tv;
gettimeofday(&tv, NULL);
return tv.tv_sec * 1000LL + tv.tv_usec / 1000;
```

---

## Core Algorithms

### Collision Detection
**Function:** `canPlace()`

**Pseudocode:**
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

### Line Clearing
**Function:** `removeLines()`

**Pseudocode:**
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
            
            // Shift rows down
            for k from i down to 1:
                for j in 0 to BOARD_WIDTH-1:
                    game.board[k][j] = game.board[k-1][j]
            
            // Clear top row
            for j in 0 to BOARD_WIDTH-1:
                game.board[0][j] = 0
            
            i++  // Re-check current row
    
    return linesRemoved
```

### Piece Rotation
**Function:** `rotatePiece()`

**Matrix Transformation:**
```
Rotation formula (90° clockwise):
    rotated[i][j] = original[SIZE-1-j][i]

Visual example:
    0 1 2 3         3 2 1 0
    . # # #         . . # .
    . . # .    →    . # # .
    . . . .         . . # .
    . . . .         . . # .
    
Index mapping:
    [0,1] → [1,3]
    [0,2] → [2,3]
    [0,3] → [3,3]
    [1,2] → [2,2]
```

---

## Game Loop

**Function:** `gameLoop()` in `main.cpp`

**Main Loop Algorithm:**

```
Initialize lastFallTime = getCurrentTimeMs()

while not game.gameOver:
    // 1. Render
    draw(game)
    
    // 2. Handle Input (non-blocking)
    if keyPressed():
        key = getKey()
        
        switch key:
            'a'/'A': moveLeft(game)
            'd'/'D': moveRight(game)
            'w'/'W': rotatePiece(game)
            's'/'S': 
                if moveDown(game):
                    score += 1  // Soft drop bonus
            ' ':     hardDrop(game)
            'q'/'Q': gameOver = true
    
    // 3. Automatic Falling
    currentTime = getCurrentTimeMs()
    if currentTime - lastFallTime >= currentSpeed:
        if not moveDown(game):
            // Piece landed
            placePiece(game)
            lines = removeLines(game)
            updateScoreAndSpeed(game, lines)
            spawnNewPiece(game)
        
        lastFallTime = currentTime
    
    // 4. Frame Rate Control
    sleepMs(30)  // ~33 FPS
```

**Timing Diagram:**
```
Time (ms):   0      30     60     90     120    ...    500
             |      |      |      |      |      |      |
Input:       ─┐    ─┐    ─┐    ─┐    ─┐    ─┐    ─┐
Check         └─────└─────└─────└─────└─────└─────└──

Render:      ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓

Auto-Fall:   ─────────────────────────────────────┐
(500ms)                                            └── Fall!
```

**Hard Drop Algorithm:**
```cpp
function hardDrop(game):
    while moveDown(game):
        score += 2  // Hard drop bonus
    // Piece automatically placed after loop
```

---

## Cross-Platform Compatibility

### Preprocessor Directives
The codebase uses conditional compilation:

```cpp
#ifdef _WIN32
    // Windows-specific code
#else
    // Linux/Mac-specific code
#endif
```

### Platform Differences

| Feature | Windows | Linux/Mac |
|---------|---------|-----------|
| **Input Detection** | `_kbhit()` from `<conio.h>` | Terminal flags + `fcntl()` |
| **Character Read** | `_getch()` from `<conio.h>` | `getchar()` with termios |
| **Sleep** | `Sleep(ms)` from `<windows.h>` | `usleep(us)` from `<unistd.h>` |
| **Timing** | `GetTickCount()` | `gettimeofday()` |
| **Clear Screen** | `system("cls")` | `system("clear")` |

### Terminal Configuration (Unix)

**Non-Canonical Mode:**
```cpp
struct termios newt;
newt.c_lflag &= ~(ICANON | ECHO);  // Disable line buffering and echo
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
```

**Non-Blocking I/O:**
```cpp
int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
```

---

## Build System

### Windows - `build.bat` / `run.bat`

**Build Command:**
```batch
g++ -std=c++17 -Wall -o tetris.exe main.cpp piece.cpp board.cpp display.cpp input.cpp
```

**Flags:**
- `-std=c++17`: Use C++17 standard
- `-Wall`: Enable all warnings
- `-o tetris.exe`: Output executable name

### Linux/Mac - `Makefile`

**Make Targets:**
```makefile
all:        # Build all executables
run-main:   # Build and run main executable
clean:      # Remove build directory
list:       # List available executables
```

**Build Process:**
1. Compile non-main sources to object files (`.o`)
2. Link main source with object files to create executable

**Example:**
```bash
make             # Compile
make run-main    # Compile and run
make clean       # Clean build files
```

---

## Performance Considerations

### Time Complexity Analysis

| Function | Complexity | Notes |
|----------|------------|-------|
| `createPiece()` | O(16) = O(1) | Fixed 4×4 matrix copy |
| `canPlace()` | O(16) = O(1) | Fixed 4×4 matrix check |
| `rotatePiece()` | O(16) = O(1) | Fixed matrix transformation |
| `placePiece()` | O(16) = O(1) | Fixed 4×4 matrix write |
| `removeLines()` | O(H²×W) | Worst: 20×20×10 = 4000 ops |
| `draw()` | O(H×W) | 20×10 = 200 cells |

### Space Complexity

| Structure | Size | Notes |
|-----------|------|-------|
| `GameState` | ~800 bytes | Board: 20×10×4 = 800 bytes |
| `Piece` | ~80 bytes | Shape: 4×4×4 = 64 bytes + metadata |
| Display buffer | 400 bytes | 20×10×2 = 400 bytes (char array) |

**Total Memory:** < 2 KB

### Frame Rate
- Target: ~33 FPS (30ms delay)
- Input polling: Every frame
- Render: Every frame
- Fall timer: Variable (100-500ms)

---

## Error Handling

### Game Over Detection
**Condition:** New piece cannot be placed at spawn position
```cpp
if (!canPlace(game, game.currentPiece, game.currentPiece.x, game.currentPiece.y)) {
    game.gameOver = true;
}
```

### Boundary Checks
All movement functions use `canPlace()` to validate:
- Board boundaries (0 ≤ x < 10, 0 ≤ y < 20)
- Collision with existing pieces

### Invalid Rotation
If rotation causes collision, keep original orientation:
```cpp
if (canPlace(game, rotated, rotated.x, rotated.y)) {
    game.currentPiece = rotated;  // Apply rotation
}
// else: ignore rotation
```

---

## Future Enhancements

### Potential Improvements
1. **Wall Kicks:** Allow rotation near walls with position adjustment
2. **Ghost Piece:** Show where piece will land
3. **Hold Piece:** Ability to store one piece for later
4. **T-Spin Detection:** Bonus points for advanced moves
5. **Color Support:** ANSI color codes for different pieces
6. **High Score:** Persistent storage of best scores
7. **Difficulty Modes:** Easy/Normal/Hard presets
8. **Sound Effects:** Terminal beep for events

### Extensibility
The modular design allows easy addition of:
- New piece types (modify `SHAPES` array)
- Custom scoring systems (modify `updateScoreAndSpeed()`)
- Different board sizes (change `BOARD_WIDTH`/`BOARD_HEIGHT`)
- Alternative controls (modify input handling in `main.cpp`)

---

## References

- **Tetris Guideline:** Official rules and specifications
- **Tetromino Wiki:** Piece shapes and rotation systems
- **SRS (Super Rotation System):** Advanced rotation algorithm (not implemented)

---

**Document Version:** 1.0  
**Last Updated:** December 2025  
**Codebase:** Do-An-KNNN-TETRIS
