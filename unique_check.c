/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:38:10 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 17:15:59 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Return 1 if placing `num` at grid[row][col] does NOT duplicate
// that number in the same row or column; otherwise return 0.
int is_unique(int grid[4][4], int row, int col, int num)
{
    int index;

    index = 0;
    while (index < 4)                       // check across 4 cells
    {
        if (grid[row][index] == num)        // same row duplicate?
            return (0);
        if (grid[index][col] == num)        // same column duplicate?
            return (0);
        index++;
    }
    return (1);                             // no conflicts found
}
