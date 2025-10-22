/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebin-ahm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:56:11 by ebin-ahm          #+#    #+#             */
/*   Updated: 2025/10/18 19:26:13 by ebin-ahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Fill an array `vals[16]` with exactly sixteen digits (1..4) parsed
// from the input string `s`. Non-digit separators like spaces/tabs/newlines
// are allowed. Returns 1 on success (exactly 16 values), 0 otherwise.
int fill_values(const char *s, int vals[16])
{
    int i;      // index scanning the input string
    int n;      // how many values we've written into vals[]
    int k;      // lookahead index to inspect a token
    int ok;     // whether the current token is valid (all '1'..'4')

    i = 0;
    n = 0;
    while (s[i] && n < 16)                          // parse until end or 16 vals
    {
        // skip any whitespace separators
        while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
            i++;

        if (!s[i])                                  // early end after whitespace
            break;

        k = i;                                      // start of token
        ok = 1;                                     // assume token is valid

        // scan the token until next whitespace
        while (s[k] && s[k] != ' ' && s[k] != '\t' && s[k] != '\n')
        {
            if (s[k] < '1' || s[k] > '4')          // any non 1..4 makes it invalid
                ok = 0;
            k++;
        }

        if (ok)
            // copy each digit ('1'..'4') into vals[n] as int (1..4)
            while (i < k && n < 16)
                vals[n++] = s[i++] - '0';
        else
            // skip the invalid token entirely
            i = k;
    }
    return (n == 16);                               // must have exactly 16 values
}

// Convert the flat 16-element list into the 4x4 `clues` matrix.
// Layout is:
//   clues[0][i] = top    clues (i = 0..3)
//   clues[1][i] = bottom clues
//   clues[2][i] = left   clues
//   clues[3][i] = right  clues
int parse_clues(const char *str, int clues[4][4])
{
    int v[16];       // temporary flat array
    int i;           // column index 0..3

    if (!fill_values(str, v))       // parse into v[16], validate
        return (0);

    i = 0;
    while (i < 4)
    {
        clues[0][i] = v[i];         // top
        clues[1][i] = v[4 + i];     // bottom
        clues[2][i] = v[8 + i];     // left
        clues[3][i] = v[12 + i];    // right
        i++;
    }
    return (1);
}
