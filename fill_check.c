/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:00:44 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 17:24:54 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// external helpers provided elsewhere
int is_unique(int grid[4][4], int row, int col, int num);
int count_visible(int *line);

// Check a fully-filled 4-cell line against two clues (front/back).
// Returns 1 if both directions match; otherwise 0.
static int check_two_sides(int line[4], int a, int b)
{
    int rev[4];

    if (count_visible(line) != a)      // forward direction
        return (0);

    // build reversed array to check the back clue
    rev[0] = line[3];
    rev[1] = line[2];
    rev[2] = line[1];
    rev[3] = line[0];

    if (count_visible(rev) != b)       // backward direction
        return (0);

    return (1);
}

// If the line contains any zero (incomplete), accept it (cannot verify yet).
// Otherwise, verify the line matches the two clues.
static int check_line_if_full(int line[4], int front, int back)
{
    if (line[0] == 0 || line[1] == 0 || line[2] == 0 || line[3] == 0)
        return (1);                     // partial line is tentatively OK
    return (check_two_sides(line, front, back));
}

// Try placing `num` at linear index `pos` (row=pos/4, col=pos%4).
// Checks uniqueness and partial visibility consistency.
// Temporarily writes the number into the grid to test, then restores it.
// Returns 1 if safe to place, 0 otherwise.
int is_safe(int grid[4][4], int clues[4][4], int pos, int num)
{
    int row;        // row index 0..3
    int col;        // col index 0..3
    int rline[4];   // snapshot of the row after tentative placement
    int cline[4];   // snapshot of the col after tentative placement

    row = pos / 4;
    col = pos % 4;

    // immediate row/col uniqueness check
    if (!is_unique(grid, row, col, num))
        return (0);

    // tentatively place the number
    grid[row][col] = num;

    // check the row against left/right clues if the row becomes full
    rline[0] = grid[row][0];
    rline[1] = grid[row][1];
    rline[2] = grid[row][2];
    rline[3] = grid[row][3];
    if (!check_line_if_full(rline, clues[2][row], clues[3][row]))
        return (grid[row][col] = 0, 0); // restore and fail

    // check the column against top/bottom clues if the column becomes full
    cline[0] = grid[0][col];
    cline[1] = grid[1][col];
    cline[2] = grid[2][col];
    cline[3] = grid[3][col];
    if (!check_line_if_full(cline, clues[0][col], clues[1][col]))
        return (grid[row][col] = 0, 0); // restore and fail

    // restore to empty; caller will actually place it if they commit
    grid[row][col] = 0;
    return (1);
}
