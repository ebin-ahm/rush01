/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:08:48 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 17:09:08 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// we only need is_safe, because the solver calls it before placing numbers
int is_safe(int grid[4][4], int clues[4][4], int pos, int num);

// move to the next cell index (pos goes 0..15)
int next_pos(int pos)
{
    return (pos + 1);
}

/*
** Recursively fill the grid cell-by-cell using backtracking.
** pos = 0..15 linear index (row = pos/4, col = pos%4)
**
** Algorithm:
** 1) If pos == 16 → all cells are filled → puzzle solved
** 2) If cell already has a number, skip to the next position
** 3) Try numbers 1..4
**       - only place it if is_safe() returns true
**       - recurse
** 4) If recursion fails, undo the number (backtrack)
** 5) If all numbers fail, return 0 (dead end)
*/
int solve_pos(int grid[4][4], int clues[4][4], int pos)
{
    int row;
    int col;
    int num;

    if (pos == 16)                          // base case: filled all 16 cells
        return (1);

    row = pos / 4;
    col = pos % 4;

    if (grid[row][col] != 0)                // skip pre-filled (not needed here but good safety)
        return (solve_pos(grid, clues, next_pos(pos)));

    num = 1;
    while (num <= 4)
    {
        if (is_safe(grid, clues, pos, num)) // check uniqueness + visibility rules
        {
            grid[row][col] = num;           // place number
            if (solve_pos(grid, clues, next_pos(pos)))
                return (1);                 // success propagates upward

            grid[row][col] = 0;             // failure → undo and try next number
        }
        num++;
    }
    return (0);                              // dead end → backtrack
}

/*
** Entry function. Starts solving at pos 0.
*/
int solve(int grid[4][4], int clues[4][4])
{
    return (solve_pos(grid, clues, 0));
}
