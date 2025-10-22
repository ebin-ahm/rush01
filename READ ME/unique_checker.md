Purpose

    unique_check.c ensures row/column uniqueness: a number may appear once per row and once per column. 

Function
    is_unique(int grid[4][4], int row, int col, int num)

Iterates index 0..3:

    if any grid[row][index] == num → not unique in row

    if any grid[index][col] == num → not unique in column

Returns 1 if no duplicates are found. 

Why do uniqueness before visibility?

    It prunes the search tree early.

    Visibility needs more work (constructing lines & counting).

    If it’s already illegal by uniqueness, no need to do heavier checks.

Example

    Row currently [_ 2 3 _], trying 2 at col 0 fails immediately (duplicate).
    Early failure = faster backtracking.