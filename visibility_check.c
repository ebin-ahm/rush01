/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:41:24 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 17:15:33 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Count how many buildings are visible when scanning the 4 numbers in `line`
// from left to right. Each time we see a taller number than all previous, it
// increases the visible count.
int count_visible(int *line)
{
    int index;      // position in line
    int max;        // tallest seen so far
    int count;      // visible buildings

    index = 0;
    max = 0;
    count = 0;
    while (index < 4)
    {
        if (line[index] > max)   // new tallest?
        {
            max = line[index];   // update tallest
            count++;             // we can see it
        }
        index++;
    }
    return (count);
}

// Verify that the fully-filled grid `g` matches all 16 clues `c`.
// For each index 0..3:
//   - l[...] is the row (left→right), r[...] is the column (top→bottom).
//   - We check both directions: normal and reversed, using the clues order:
//       c[2][i] = left  seen on row i
//       c[3][i] = right seen on row i
//       c[0][i] = top   seen on column i
//       c[1][i] = bottom seen on column i
int check_visibility(int g[4][4], int c[4][4]) //didn't use this at all thought
{
    int l[4];       // current row (left→right)
    int r[4];       // current column (top→bottom)
    int index;      // row/column index
    int cell;       // 0..3 within the row/column

    index = 0;
    while (index < 4)
    {
        cell = 0;
        while (cell < 4)
        {
            l[cell] = g[index][cell];   // row index, move across columns
            r[cell] = g[cell][index];   // column index, move down rows
            cell++;
        }

        // Check both directions against the corresponding clues.
        // The compound literal (int [4]){...} builds a reversed view quickly.
        if (count_visible(l) != c[2][index]                                     // left
         || count_visible((int [4]){l[3], l[2], l[1], l[0]}) != c[3][index]     // right
         || count_visible(r) != c[0][index]                                     // top
         || count_visible((int [4]){r[3], r[2], r[1], r[0]}) != c[1][index])    // bottom
            return (0);

        index++;
    }
    return (1);    // all rows/cols match their visibility clues
}
