# 🧩 Skyscraper Puzzle Solver (4×4)

This project implements a **4×4 Skyscraper puzzle solver** in pure C.  
It follows the same logic used in the 42 Piscine project *rush01* — using **backtracking**, **visibility checking**, and **constraint validation**.

---

## 🏙️ 1. What Is the Skyscraper Puzzle?

Imagine a city grid of **4 × 4 buildings**.  
Each cell must contain a building height from **1 to 4**, and every row/column must include all four heights (no duplicates).

Around the grid, there are **16 clues** that tell you how many buildings you can “see” from that side —  
taller buildings hide the shorter ones behind them.


If you stand on the left side of a row and can see **3 buildings**,  
that means the sequence (from left → right) increases in height three times.

---

## ⚙️ 2. Input Format (The 16 Clues)

The program expects **one argument** containing **16 numbers (1–4)** separated by spaces:


Internally, the clues are stored as:

| Row | Meaning | Example |
|------|----------|----------|
| 0 | Top clues | `4 3 2 1` |
| 1 | Bottom clues | `1 2 2 2` |
| 2 | Left clues | `4 3 2 1` |
| 3 | Right clues | `1 2 2 2` |

---

## 🧠 3. Program Flow Overview

The solver works in **three main stages**:


1. **Parser** (`parser.c`)  
   – Reads and validates 16 clues from the command line.  
2. **Solver** (`solver.c`)  
   – Recursively fills the 4×4 grid, one cell at a time.  
3. **Constraint Checkers**  
   - `is_unique()` → no duplicates in row/col  
   - `is_safe()` → combines uniqueness + partial visibility  
   - `check_visibility()` → validates final solution  
4. **Display** (`main.c`)  
   – Prints the solved grid or `"Error"` if impossible.

---

## 🔁 4. Backtracking Algorithm Explained

Backtracking = *“try, test, undo, retry.”*


Every call represents a cell.  
If the solver finds a contradiction, it undoes the move and tries the next number.

---

## 👁️ 5. Visibility Rule (count_visible)

From any side, count how many buildings are visible.

Example line: `[2 1 4 3]`

- Left → Right view:  
  `2 (see 1) (see 4 since 4 > 2) (ignore 3 since 3 < 4)`  
  → **3 visible**  
- Right → Left view: `[3 4 1 2]` → **2 visible**

This rule ensures each row/column satisfies the side clues.

---

## 🧩 6. File-by-File Breakdown

| File | Purpose |
|------|----------|
| **main.c** | Handles input, initializes grid, calls solver, prints result |
| **parser.c** | Converts 16-clue string into 4×4 array |
| **unique_check.c** | Ensures no duplicates in rows/columns |
| **visibility_check.c** | Counts visible buildings & verifies final grid |
| **fill_check.c** | Combines uniqueness + partial visibility for safety checks |
| **solver.c** | Backtracking recursion engine |

---

## 🔧 7. Build & Run

### Compile manually
```bash
cc -Wall -Wextra -Werror *.c -o rush01

             ┌────────────────────┐
             │   main()           │
             │ parse_clues(argv)  │
             │ init grid[4][4]    │
             └────────┬───────────┘
                      ↓
               ┌─────────────┐
               │  solve()    │
               │ recursion   │
               └─────┬───────┘
                     ↓
            ┌─────────────────┐
            │  is_safe()      │
            │  - is_unique()  │
            │  - check_line() │
            └─────────────────┘
                     ↓
             if success → print grid
             else → "Error"
