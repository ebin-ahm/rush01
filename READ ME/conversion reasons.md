# Skyscraper Conversions (ASCII + Which Functions Use Them)

This document explains the 3 critical conversions used in the solver and
lists exactly **which functions** apply each conversion and **why**.

 1. Clues string (16 digits) → clues[4][4] matrix
 2. Linear position `pos` → (row, col) using `/` and `%`
 3. Row/column slices: `rline` and `cline` for visibility checks

All diagrams are ASCII for easy copy/paste and terminal viewing.


============================================================
1) CLUES STRING → 4×4 CLUES MATRIX
============================================================

INPUT FORMAT (from argv[1]):
---------------------------------
A single string holding 16 values from '1' to '4', e.g.:

    "t0 t1 t2 t3  b0 b1 b2 b3  l0 l1 l2 l3  r0 r1 r2 r3"

Example:

    "4 3 2 1  1 2 2 2  4 3 2 1  1 2 2 2"


INTERNAL STORAGE (clues[4][4]):
---------------------------------
Parser fills clues as:

    clues[0][i] = top[i]
    clues[1][i] = bottom[i]
    clues[2][i] = left[i]
    clues[3][i] = right[i]

ASCII grid layout:

                  (view from top)
                t0  t1  t2  t3
                 ↑
    l0  grid row0  r0
    l1  grid row1  r1
    l2  grid row2  r2
    l3  grid row3  r3
                 ↓
                b0  b1  b2  b3
             (view from bottom)

TABLE FORM:
---------------------------------
    clues[0] = [t0, t1, t2, t3]  // top
    clues[1] = [b0, b1, b2, b3]  // bottom
    clues[2] = [l0, l1, l2, l3]  // left
    clues[3] = [r0, r1, r2, r3]  // right


WHO USES THIS & WHY:
---------------------------------
- `fill_values(const char *s, int vals[16])`
  • Parses the raw string into exactly 16 ints (1..4) to ensure validity before mapping. :contentReference[oaicite:0]{index=0}

- `parse_clues(const char *str, int clues[4][4])`
  • Maps the flat `v[16]` into the 4×4 `clues` layout shown above so later checks can index by side & column/row. :contentReference[oaicite:1]{index=1}

- `main(int argc, char **argv)`
  • Calls `parse_clues` to build `clues` prior to solving; prints `Error` if parsing fails. :contentReference[oaicite:2]{index=2}

- `check_visibility(int g[4][4], int c[4][4])`
  • Relies on the exact side ordering (top/bottom/left/right) when comparing each line’s visibility to `c`. :contentReference[oaicite:3]{index=3}



============================================================
2) LINEAR POSITION → (row, col) USING `/` AND `%`
============================================================

The solver walks the 4×4 grid as a SINGLE LINEAR INDEX pos = 0..15.

To convert `pos` into grid coordinates:

    row = pos / 4      (integer division → 0..3)
    col = pos % 4      (modulo → remainder 0..3)

This keeps recursion simple (linear), while reads/writes still go to 2D cells.


ASCII TABLE:
---------------------------------
| pos | row=pos/4 | col=pos%4 | cell |
|-----|-----------|-----------|-------|
|  0  |     0     |     0     | (0,0) |
|  1  |     0     |     1     | (0,1) |
|  2  |     0     |     2     | (0,2) |
|  3  |     0     |     3     | (0,3) |
|  4  |     1     |     0     | (1,0) |
|  5  |     1     |     1     | (1,1) |
|  6  |     1     |     2     | (1,2) |
|  7  |     1     |     3     | (1,3) |
|  8  |     2     |     0     | (2,0) |
|  9  |     2     |     1     | (2,1) |
| 10  |     2     |     2     | (2,2) |
| 11  |     2     |     3     | (2,3) |
| 12  |     3     |     0     | (3,0) |
| 13  |     3     |     1     | (3,1) |
| 14  |     3     |     2     | (3,2) |
| 15  |     3     |     3     | (3,3) |


WHO USES THIS & WHY:
---------------------------------
- `solve_pos(int grid[4][4], int clues[4][4], int pos)`
  • Converts `pos` to `(row, col)` for reading/writing `grid[row][col]` during recursion. :contentReference[oaicite:4]{index=4}

- `is_safe(int grid[4][4], int clues[4][4], int pos, int num)`
  • Also derives `(row, col)` from `pos` to test uniqueness and partial visibility for the *affected* row & column. :contentReference[oaicite:5]{index=5}

- `solve(int grid[4][4], int clues[4][4])`
  • Starts at `pos=0`, relying on the same mapping as it recurses through all 16 cells. :contentReference[oaicite:6]{index=6}



============================================================
3) RLINE & CLINE (ROW/COLUMN SLICES, HIGH SCRUTINY)
============================================================

When testing a number at (row, col), we build these fixed-size slices:

    rline = { grid[row][0], grid[row][1], grid[row][2], grid[row][3] }
    cline = { grid[0][col], grid[1][col], grid[2][col], grid[3][col] }

These are always length 4 and let us run visibility checks line-by-line.


ASCII GRID (example row=2,col=1):
---------------------------------
Indexes shown as (r,c):

    (2,0) (2,1) (2,2) (2,3)   ---> rline = [ g[2][0], g[2][1], g[2][2], g[2][3] ]
      |      |      |      \
      v      v      v       v
    (0,1) (1,1) (2,1) (3,1) ---> cline = [ g[0][1], g[1][1], g[2][1], g[3][1] ]


PARTIAL vs FULL VISIBILITY CHECKS:
---------------------------------
If a line contains any 0, we DEFER visibility:

    [2, 0, 4, 0]  -> partial, do NOT check yet

If all 4 are filled, we check BOTH directions:

LEFT  -> count_visible(rline)
RIGHT -> count_visible(reversed_rline)

TOP   -> count_visible(cline)
BOTTOM-> count_visible(reversed_cline)


ASCII “COUNT VISIBLE” LOGIC:
---------------------------------
Scan left to right, counting new maxima:

Example line: [2, 1, 4, 3]

- Start: max=0, visible=0
- 2 > 0 → max=2, visible=1
- 1 > 2 → no change
- 4 > 2 → max=4, visible=2
- 3 > 4 → no change

Result: visible = 2

Reversed line example:
    [3, 4, 1, 2] → visible = 2


WHO BUILDS/USES THESE & WHY:
---------------------------------
- `is_safe(int grid[4][4], int clues[4][4], int pos, int num)`
  • Builds `rline` and `cline` *after* a temporary placement to check if the
    newly affected row/column is still consistent with clues **when full**.
    If the line is partial (has 0), it defers the check to avoid false negatives. :contentReference[oaicite:7]{index=7}

- `check_line_if_full(int line[4], int front, int back)`
  • Returns 1 immediately if the line is partial (any zero). Otherwise it
    validates both directions via `check_two_sides`. :contentReference[oaicite:8]{index=8}

- `check_two_sides(int line[4], int a, int b)`
  • Computes visibility for the line and its reverse, compares to the two clues
    (front/back) provided for that line. :contentReference[oaicite:9]{index=9}

- `check_visibility(int g[4][4], int c[4][4])`
  • On a *completed* grid, reconstructs each row (`l`) and column (`r`) and
    compares visibility in both directions against the matching clues for
    every index 0..3. This is the final all-sides validation. :contentReference[oaicite:10]{index=10}

- `count_visible(int *line)`
  • Primitive used by the above routines to count “new maxima” during a scan. :contentReference[oaicite:11]{index=11}

- `is_unique(int grid[4][4], int row, int col, int num)`
  • Not a visibility routine, but it’s always run *before* building lines to
    prune obvious row/column duplicates quickly. :contentReference[oaicite:12]{index=12}



============================================================
END-TO-END SUMMARY
============================================================

Conversion Path:
---------------------------------
STRING (16 tokens)
   → flat int[16]
      → clues[4][4]   (top/bottom/left/right)
         • Built by: fill_values + parse_clues (parser.c)
         • Used by: solver (to guide checks), final visibility

pos (0..15)
   → (row,col) via / and %
         • Used by: solve_pos / is_safe

(row,col)
   → rline & cline    (4-element slices)
      → visibility checks (forward + reverse)
         • Built by: is_safe (partial), check_visibility (final)
         • Verified by: check_line_if_full, check_two_sides, count_visible

Also:
- Early pruning: is_unique (row/col duplicates)
- Final output / errors: main.c printing and error path


REFERENCES (SOURCE FILES)
---------------------------------
- main.c (entry, printing, error path)  :contentReference[oaicite:13]{index=13}
- parser.c (fill_values, parse_clues)   :contentReference[oaicite:14]{index=14}
- unique_check.c (is_unique)            :contentReference[oaicite:15]{index=15}
- visibility_check.c (count_visible, check_visibility)  :contentReference[oaicite:16]{index=16}
- fill_check.c (is_safe, check_line_if_full, check_two_sides)  :contentReference[oaicite:17]{index=17}
- solver.c (solve, solve_pos, next_pos) :contentReference[oaicite:18]{index=18}
