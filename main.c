/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 17:11:11 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 17:13:57 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>                  // write

// forward declarations (implemented elsewhere)
int parse_clues(const char *s, int clues[4][4]);
int solve(int grid[4][4], int clues[4][4]);
int check_visibility(int grid[4][4], int clues[4][4]);

// print a single digit (1..4) as a character
void putnbr_c(int n)
{
    char c;

    c = n + '0';                    // convert number 0..9 to ASCII
    write(1, &c, 1);                // write the character to stdout
}

// pretty-print a 4x4 grid with spaces between numbers and newlines per row
void print_grid(int grid[4][4])
{
    int row;
    int col;

    row = 0;
    while (row < 4)                 // for each row
    {
        col = 0;
        while (col < 4)             // for each column in the row
        {
            putnbr_c(grid[row][col]);       // print the cell value
            if (col < 3)                    // add a space between numbers
                write(1, " ", 1);
            col++;
        }
        write(1, "\n", 1);          // newline at end of row
        row++;
    }
}

// program entry point
int main(int argc, char **argv)
{
    int clues[4][4];                // the 16 clues arranged as 4x4 (top/bot/left/right)
    int grid[4][4];                 // the puzzle grid (to be filled by solver)
    int row;
    int col;

    // initialize the grid with zeros (0 = empty cell)
    row = 0;
    while (row < 4)
    {
        col = 0;
        while (col < 4)
        {
            grid[row][col] = 0;
            col++;
        }
        row++;
    }

    // require exactly one argument (the 16 clues string),
    // parse clues into a 4x4 array, then attempt to solve.
    if (argc != 2 || !parse_clues(argv[1], clues) || !solve(grid, clues ) || !check_visibility(grid, clues))
    {
        write(1, "Error\n", 6);      // any failure prints "Error" and exits 1
        return (1);
    }

    // if solved, print the filled 4x4 grid
    print_grid(grid);
    return (0);
}
