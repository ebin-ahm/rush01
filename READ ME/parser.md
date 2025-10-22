Purpose

    parser.c parses and validates the 16 clues string and maps it into a structured 4×4 matrix: top/bottom/left/right. 

Input Format → Internal Format

    Given (string):
    "a0 a1 a2 a3 b0 b1 b2 b3 l0 l1 l2 l3 r0 r1 r2 r3" where each token ∈ {1,2,3,4}.

Mapped to (matrix):

    clues[0][i] = a[i] (top, i=0..3)

    clues[1][i] = b[i] (bottom)

    clues[2][i] = l[i] (left)

    clues[3][i] = r[i] (right)  

    This mirrors how visibility_check.c consumes clues by index.

Functions
    fill_values(const char *s, int vals[16])

    Scans s, skipping whitespace, gathering exactly 16 digits 1..4 into vals.

    Rejects any token that contains chars outside ‘1’..‘4’.

    Returns 1 if and only if we collected exactly 16 values. 


Why strict token validation?
    It prevents hidden errors (e.g., 10 or 5 or letters). A token containing any bad char is skipped entirely, which enforces clean inputs.

parse_clues(const char *str, int clues[4][4])

    Calls fill_values(str, v) to produce v[16].

    Splits v into four groups of four: top, bottom, left, right, by offsets 0, 4, 8, 12.

    Returns 1 on success. 

Example Conversion

Input string
    "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

After fill_values
    v = [4,3,2,1, 1,2,2,2, 4,3,2,1, 1,2,2,2]

Clues matrix

    clues[0]=[4,3,2,1]  // top
    clues[1]=[1,2,2,2]  // bottom
    clues[2]=[4,3,2,1]  // left
    clues[3]=[1,2,2,2]  // right

This shape is crucial for the visibility checks later.