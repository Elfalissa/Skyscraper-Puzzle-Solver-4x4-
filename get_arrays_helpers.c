/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arrays_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:21:11 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/04 21:55:50 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

///////////////////////////////////
//Helping functions for the get_arrays function
///////////////////////////////////

/**
 * Count how many skyscrapers are visible from one side of a row.
 *
 * @param arr  A row of 4 integers representing skyscraper heights (1–4).
 *
 * @return     The number of visible skyscrapers when viewed from the
 *             start of `arr`.
 *
 * Example:
 *   {1, 3, 4, 2} -> 3 (see 1, then 3, then 4)
 *   {4, 1, 3, 2} -> 1 (see only 4, the rest are hidden)
 *
 * Visibility rule:
 * A skyscraper is visible if it is taller than all skyscrapers before it.
 */
int	count_visible(int arr[4])
{
	int	max;
	int	visible;
	int	i;

	max = 0;
	visible = 0;
	i = 0;
	while (i < 4)
	{
		if (arr[i] > max)
		{
			visible++;
			max = arr[i];
		}
		i++;
	}
	return (visible);
}

/**
 * Check for duplicates in part of an array.
 *
 * @param arr  The array of integers.
 * @param l    The starting index of the section to check.
 * @param i    The index of the current element being compared.
 *
 * @return     1 if a duplicate of arr[i] is found in arr[l..i-1], otherwise 0.
 *
 * This helper is used during permutation generation to avoid
 * repeating the same number within a row/column.
 */
int	has_duplicate(int arr[], int l, int i)
{
	int	j;

	j = l;
	while (j < i)
	{
		if (arr[j] == arr[i])
			return (1);
		j++;
	}
	return (0);
}

/**
 * Save a valid row permutation into the results array.
 *
 * @param arr   The current permutation of 4 numbers.
 * @param ctx   Context array used during permutation:
 *              - ctx[0] -> pointer to int a (visibility from one side)
 *              - ctx[1] -> pointer to int b (visibility from opposite side)
 *              - ctx[2] -> pointer to int count (number of stored results)
 *              - ctx[3] -> pointer to int[24][4] result array
 *
 * This function checks whether the current permutation `arr`
 * satisfies the visibility constraints (a from left, b from right).
 * If valid, it copies `arr` into the next available row of `result`.
 */
void	save_result(int arr[], void *ctx[4])
{
	int		reversed[4];
	int		i;
	int		*count;
	int		(*result)[4];

	count = ctx[2];
	result = ctx[3];
	reverse(arr, reversed);
	if (count_visible(arr) == *(int *)ctx[0]
		&& count_visible(reversed) == *(int *)ctx[1])
	{
		i = 0;
		while (i < 4)
		{
			result[*count][i] = arr[i];
			i++;
		}
		(*count)++;
	}
}

/**
 * Generate all permutations of the base array under skyscraper rules.
 *
 * @param arr  The current array of integers being permuted.
 * @param l    The left bound (current position to fix).
 * @param r    The right bound (end of array, usually 3).
 * @param ctx  Context array (same as in save_result).
 *
 * This function recursively generates all permutations of `arr`.
 * At each complete permutation (when l == r), it calls save_result
 * to check constraints and store the valid solution.
 */
void	permute(int arr[], int l, int r, void *ctx[4])
{
	int	i;

	if (l == r)
		return (save_result(arr, ctx));
	i = l;
	while (i <= r)
	{
		if (!has_duplicate(arr, l, i))
		{
			swap(&arr[l], &arr[i]);
			permute(arr, l + 1, r, ctx);
			swap(&arr[l], &arr[i]);
		}
		i++;
	}
}

/**
 * Fill unused slots in the result array with zeros.
 *
 * @param result  The 24x4 result array containing row permutations.
 * @param start   The index from which unused rows begin.
 *
 * After generating valid permutations, the remaining rows
 * in the result array are cleared by filling them with zeros.
 * This ensures the result array has a consistent size (24x4)
 * and allows `len()` to detect the actual count of solutions.
 */
void	clear_tail(int result[24][4], int start)
{
	int	i;
	int	j;

	i = start;
	while (i < 24)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = 0;
			j++;
		}
		i++;
	}
}
