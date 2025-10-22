Purpose

    visibility_check.c performs final, full-grid validation against all 16 clues using the helper count_visible. This runs once the grid is fully filled. 

Core Ideas
    A) count_visible(int *line)

    Scans a length-4 array left→right.

    Keeps max (tallest so far).

    Each time line[i] > max, increment count and set max=line[i].

    Returns total visible. 

4. visibility_check.c (1)

    Why this works:
    A higher building blocks all smaller ones behind it. Counting “new maxima” equals counting visible buildings.

    B) Building rline & cline (concept)

    For each index i:

    Row l: l[c] = g[i][c] (left→right across columns c=0..3)

    Column r: r[rw] = g[rw][i] (top→bottom down rows rw=0..3)

    Then match both directions:

    left vs right (using l and reversed l)

    top vs bottom (using r and reversed r)
    All 4 checks must match for each i. 


C) Why reverse with a compound literal?

    To check the opposite side’s clue quickly:
    count_visible((int[4]){l[3], l[2], l[1], l[0]})
    No extra buffers needed; it’s compact and clear. 

4. visibility_check.c (1)

Deep Dive: rline & cline (high scrutiny)

    Let’s say the grid row 2 (0-based) is:

    g[2] = [2, 1, 4, 3]


    l = [2,1,4,3] → count_visible(l) = 3 (left clue must be 3)

    reversed l = [3,4,1,2] → count_visible = 2 (right clue must be 2)

    For columns, suppose column 1 is:

    [g[0][1], g[1][1], g[2][1], g[3][1]] = [2,3,1,4]


    r = [2,3,1,4] → visible = 3 (top clue must be 3)

    reversed r = [4,1,3,2] → visible = 1 (bottom clue must be 1)

    These four checks enforce both directions per row and per column. 

4. visibility_check.c (1)

Function
    check_visibility(int g[4][4], int c[4][4])

    For each index 0..3, constructs l (row) and r (column).

Compares:

    count_visible(l) == c[2][i] (left)

    count_visible(rev(l)) == c[3][i] (right)

    count_visible(r) == c[0][i] (top)

    count_visible(rev(r)) == c[1][i] (bottom)

    Returns 1 only if all match