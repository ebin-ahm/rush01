Purpose

    solver.c drives the recursive backtracking. It linearizes the 2D grid into positions 0..15 and uses / and % to map back to (row, col) for each step. 

Why / and % here?

    pos represents the Nth cell in a 4×4 matrix (row-major order).

    row = pos / 4 gives which row this position lives in.

    col = pos % 4 gives the column offset within that row.

    This is the cleanest way to traverse the board linearly while still writing to grid[row][col]. 

Functions
next_pos(int pos)

    Returns pos + 1; used to move forward. Keeping it as a function makes the recursion intent explicit. 

    solve_pos(int grid[4][4], int clues[4][4], int pos)

Algorithm:

Base case: if pos == 16, the board is full → return 1.

    Compute row = pos / 4, col = pos % 4.

    If grid[row][col] is non-zero (pre-filled), recurse to next_pos(pos).

    Loop num=1..4:

        If is_safe(grid, clues, pos, num) → place it, recurse forward.

        If recursion fails, undo (backtrack) and try next num.

        If all options fail, return 0. 

solve(int grid[4][4], int clues[4][4])

    Starts recursion at pos = 0. 

Interaction Contract

    Calls is_safe (from fill_check.c) for smart pruning.

    Relies on is_unique (row/col duplication) and partial visibility checks.

    Stops only when a consistent full assignment is found or search space is exhausted.

Example (micro-trace)

    pos=0 → (0,0): try 1..4. Suppose 2 is safe → write 2, recurse.

    pos=1 → (0,1): try 1..4…

Whenever a choice leads to contradiction, backtrack one step and try the next number.