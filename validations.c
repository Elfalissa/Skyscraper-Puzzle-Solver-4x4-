/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:48:59 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/04 21:56:21 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * Validate the input string format.
 *
 * @param str  Input string (expected format: "x x x x x x x x x x x x x x x x").
 *
 * @return 1 if the string is valid, 0 otherwise.
 *
 * A valid string must:
 *   - Contain exactly 16 digits in the range [1–4].
 *   - Digits must be separated by single spaces.
 *   - Total string length must be 31 characters.
 *
 * Example of valid input: "2 1 4 2 2 3 1 3 2 3 1 2 2 1 3 2"
 */
int	validate_input_condition(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i % 2 == 0 && !(str[i] <= '4' && str[i] >= '1'))
		{
			return (0);
		}
		if (i % 2 != 0 && str[i] != ' ')
		{
			return (0);
		}
		i++;
	}
	if (i != 31)
	{
		return (0);
	}
	return (1);
}

/**
 * Validate border conditions for the puzzle.
 *
 * @param up     Array of 4 integers representing top constraints.
 * @param down   Array of 4 integers representing bottom constraints.
 * @param left   Array of 4 integers representing left constraints.
 * @param right  Array of 4 integers representing right constraints.
 *
 * @return 1 if constraints are logically consistent, 0 otherwise.
 *
 * Rules enforced:
 *   - If one side has 4, the opposite side must be 1.
 *   - If one side has 1, the opposite side cannot also be 1.
 *
 * Ensures no contradictions in the initial puzzle setup.
 */
int	validate_border_conditions(int *up, int *down, int *left, int *right)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((up[i] == 4 && down[i] != 1)
			|| (down[i] == 4 && up[i] != 1)
			|| (left[i] == 4 && right[i] != 1)
			|| (right[i] == 4 && left[i] != 1))
			return (0);
		if ((up[i] == 1 && down[i] == 1)
			|| (left[i] == 1 && right[i] == 1))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Check for duplicate values in columns of the field.
 *
 * @param field  4x4 matrix representing the puzzle grid.
 *
 * @return 1 if no duplicates are found in any column,
 *         0 if at least one duplicate is detected.
 *
 * Each column must contain unique numbers from 1 to 4.
 */
int	no_duplicates_in_columns(int field[4][4])
{
	int	i;
	int	j;
	int	k;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			k = i + 1;
			while (k < 4)
			{
				if (field[i][j] == field[k][j])
					return (0);
				k++;
			}
			i++;
		}
		j++;
	}
	return (1);
}

/**
 * Check for duplicate values in rows of the field.
 *
 * @param field  4x4 matrix representing the puzzle grid.
 *
 * @return 1 if no duplicates are found in any row,
 *         0 if at least one duplicate is detected.
 *
 * Each row must contain unique numbers from 1 to 4.
 */
int	no_duplicates_in_rows(int field[4][4])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = j + 1;
			while (k < 4)
			{
				if (field[i][j] == field[i][k])
					return (0);
				k++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * Verify left and right visibility constraints for all rows.
 *
 * @param field  4x4 matrix representing the puzzle grid.
 * @param left   Array of 4 integers with left-side constraints.
 * @param right  Array of 4 integers with right-side constraints.
 *
 * @return 1 if all rows satisfy their left-right visibility rules,
 *         0 otherwise.
 *
 * For each row, this function:
 *   - Generates all valid row permutations for the given left/right pair.
 *   - Checks if the current row matches at least one valid permutation.
 */
int	verification_left_right(int field[4][4], int *left, int *right)
{
	int	i;
	int	j;
	int	arrays[24][4];

	i = 0;
	while (i < 4)
	{
		get_arrays(left[i], right[i], arrays);
		j = 0;
		while (j < len(left[i], right[i]))
		{
			if (is_presented(field[i], arrays[j]))
				break ;
			j++;
		}
		if (j == len(left[i], right[i]))
			return (0);
		i++;
	}
	return (1);
}
