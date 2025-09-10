/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arrays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:43:58 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/04 21:55:45 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * Generate all valid permutations of a row/column given visibility constraints.
 *
 * @param a       The visibility constraint from one side (top or left).
 * @param b       The visibility constraint from the
 * 				  opposite side (bottom or right).
 * @param result  Output array [24][4] that will be filled with all valid
 *                permutations. Each row in `result` is a candidate permutation.
 *
 * This function assumes that `a` and `b` represent the "skyscraper puzzle"
 * visibility conditions for a single row or column. It generates all
 * permutations of numbers 1–4 that satisfy both conditions and writes them
 * into `result`. Unused slots in `result` are filled with zeros.
 */
void	get_arrays(int a, int b, int result[24][4])
{
	int		base[4];
	int		count;
	void	*ctx[4];

	base[0] = 1;
	base[1] = 2;
	base[2] = 3;
	base[3] = 4;
	count = 0;
	ctx[0] = &a;
	ctx[1] = &b;
	ctx[2] = &count;
	ctx[3] = result;
	permute(base, 0, 3, ctx);
	clear_tail(result, count);
}

/**
 * Count the number of valid row/column permutations for given constraints.
 *
 * @param a   The visibility constraint from one side (top or left).
 * @param b   The visibility constraint from the opposite side (bottom or right).
 *
 * @return    The number of valid permutations (0–24).
 *
 * This function calls `get_arrays` to generate all valid permutations
 * for a row/column under the given conditions, then counts how many
 * non-empty solutions exist. It is used to determine the search space
 * size for a particular row/column.
 */
int	len(int a, int b)
{
	int	arrays[24][4];
	int	count;

	get_arrays(a, b, arrays);
	count = 0;
	while (count < 24)
	{
		if (arrays[count][0] != 0)
			count++;
		else
			break ;
	}
	return (count);
}
