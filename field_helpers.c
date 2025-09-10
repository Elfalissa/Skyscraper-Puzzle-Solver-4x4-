/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:53:23 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/04 21:55:58 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * Transpose a 4x4 matrix.
 *
 * @param src   The input 4x4 matrix (original field).
 * @param dest  The output 4x4 matrix where the transposed values are stored.
 *
 * This function takes a 4x4 source matrix (`src`) and writes its transpose
 * into the destination matrix (`dest`). Transposition means converting
 * rows into columns, so `dest[j][i] = src[i][j]`.
 */
void	transpose_the_field(int src[4][4], int dest[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[j][i] = src[i][j];
			j++;
		}
		i++;
	}
}

/**
 * Fill a row in the 4x4 field with one of the candidate arrays.
 *
 * @param field   The 4x4 field matrix to be updated.
 * @param row     The row index in the field (0–3).
 * @param arrays  A list of candidate rows (24x4 array).
 * @param idx     The index of the candidate row to copy.
 *
 * Copies the row at `arrays[idx]` into the specified row of `field`.
 * Used to try different row configurations while solving the puzzle.
 */
void	fill_row(int field[4][4], int row, int (*arrays)[4], int idx)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		field[row][j] = arrays[idx][j];
		j++;
	}
}

/**
 * Extract 4 integers from a validated string of puzzle constraints.
 *
 * @param str    The input string containing numbers separated by spaces.
 *               Example: "2 1 4 2 2 3 1 3 2 3 1 2 2 1 3 2"
 * @param start  The starting index in the string to begin reading.
 *
 * @return       A dynamically allocated array of 4 integers.
 *
 * Reads 4 numbers from the string `str`, starting at position `start`,
 * skipping every second character (assuming format "n n n n").
 * Returns an array of 4 integers, which must be freed by the caller.
 *
 * Note: Only call this function on validated input strings
 * where the format strictly follows the puzzle rules.
 */
int	*grab_ints_from_str(char *str, int start)
{
	int	*result;
	int	i;
	int	j;

	result = malloc(4 * sizeof(int));
	i = start;
	j = 0;
	while (i < 8 + start)
	{
		if (str[i] >= '1' && str[i] <= '4')
			result[j] = str[i] - '0';
		else
			result[j] = 0;
		i += 2;
		j++;
	}
	return (result);
}
