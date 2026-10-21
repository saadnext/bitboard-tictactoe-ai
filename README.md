# 🤖 Bitboard Tic-Tac-Toe Engine with Alpha-Beta Minimax

An unbeatable Tic-Tac-Toe game engine built from scratch in C++20. This engine leverages advanced game development techniques like modern bitboard representations, object-oriented design decoupling, and in-place backtracking search to run with zero dynamic memory overhead.

---

## 🚀 Key Features

* **Bitboard Architecture:** Uses binary lookup masks via `std::bitset` to compute win states and board occupancy. This replaces slow 2D matrix iterative loops with instantaneous bitwise configurations.
* **Alpha-Beta Minimax:** Implements a highly compact, unified search tree optimization algorithm to prune irrelevant paths early, drastically minimizing node traversal count.
* **Pass-by-Reference Backtracking:** Modifies and undoes actions over a single reference instance instead of copying object frames dynamically through recursive calls.
* **C++20 & CMake Compliant:** Written with strict modern C++ compliance standards and configured cleanly using CMake.

---

## 🛠️ Architecture Overview

The source tree separates core simulation and state control from visual terminal handling and searching:

- **`src/bitboard.h`** — Fast primitive wrappers for managing bits and indices.
- **`src/board.h`** — Keeps track of active turns, piece placements, and victory masks.
- **`src/search.h`** — Houses optimized `minimax` calculation and branch evaluation pathways.
- **`src/game.h` / `main.cpp`** — Manages user interactive terminal flows and loop states.

---

## ⚙️ Compilation & Setup

### Prerequisites
Make sure you have a modern compiler supporting **C++20** (GCC 10+, Clang 10+, or MSVC 2019+) and **CMake 3.20+**.

```bash
# Clone the repository
git clone [https://github.com](https://github.com/saadnext/bitboard-tictactoe-ai)
cd bitboard-tictactoe-ai

# Create a build directory
mkdir build && cd build

# Configure and compile using CMake
cmake ..
cmake --build .

# Run the game engine binary
./engine
```
---

## 🎨 Project Origin

Developed with 💻 by **Saad rabia** strictly for fun, curiosity, and educational exploration into low-level game engine architectures and combinatorial search pruning trees. 
