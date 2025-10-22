Purpose

    fill_check.c is used during backtracking (partial grid). It checks whether tentatively placing a number is safe given uniqueness and partial visibility constraints for the affected row and column. It’s the key pruning function. 

Why / and % (transposing linear → 2D)

    The solver iterates a linear position pos ∈ [0..15].
    We map it to a 2D coordinate with:

    row = pos / 4 → integer division: 0..3
    col = pos % 4 → modulo: remainder 0..3

This is a standard mapping from linear index to matrix coordinates.
Why here? Because solver walks positions linearly while the grid is 2D. 

Data Flow in is_safe

    Compute (row, col) from pos using / and %.

    Check is_unique(grid, row, col, num) → quick prune.

    Temporarily write grid[row][col] = num.

    Build rline = { grid[row][0..3] } and check left/right clues if the row is full.

    Build cline = { grid[0..3][col] } and check top/bottom clues if the column is full.

Restore grid[row][col] = 0 and return whether safe. 

Note: the code accepts partial lines automatically in check_line_if_full—if any cell is 0, it defers visibility until the line is complete. This avoids premature rejection. 

High-Scrutiny: rline & cline during partial checks

When we tentatively place a number, only its row and column can become newly invalid.

We snapshot:

    rline = [ grid[row][0], grid[row][1], grid[row][2], grid[row][3] ]

    cline = [ grid[0][col], grid[1][col], grid[2][col], grid[3][col] ]

     check_line_if_full logic:

    If any entry is 0, it returns 1 immediately (can’t judge visibility yet).

    Else, it checks both directions using check_two_sides. 

    This design permits early pruning exactly when the line has become complete; otherwise it stays permissive.

Functions
    check_two_sides(int line[4], int a, int b)

Computes count_visible(line) and count_visible(reversed(line)), compares to a and b.

    Returns 1 if both match. 


    check_line_if_full(int line[4], int front, int back)

Quick guard: if any cell == 0 → return 1 (not ready to judge).

    Else → call check_two_sides. 


is_safe(int grid[4][4], int clues[4][4], int pos, int num)

    Does uniqueness, temporary placement, row/col partial-visibility checks, and restoration.

    Returns 1 only when the tentative placement is consistent. 

Example Walkthrough (partial grid)

    Suppose row 1 is [2, 0, 4, 0] and we try placing 3 at col 1:

    After temp write: row becomes [2, 3, 4, 0] (still not full)

    check_line_if_full(rline, leftClue, rightClue) returns 1 (defers judgment).

    If column becomes full after this placement, we check top/bottom immediately; else we defer.