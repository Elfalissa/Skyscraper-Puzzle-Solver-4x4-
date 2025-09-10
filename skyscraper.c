/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:34:17 by amanukho          #+#    #+#             */
/*   Updated: 2025/09/09 22:14:31 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

// To compile use:
// cc -Wall -Wextra -Werror -o skyscraper *.c.
// for test use:
// ./skyscraper "2 1 4 2 2 3 1 3 2 3 1 2 2 1 3 2" | cat -e
// the output should be:
// 2 4 1 3$
// 1 3 2 4$
// 4 1 3 2$
// 3 2 4 1$

/**
 * Check if a given field (4x4 grid) is a valid solution.
 *
 * @param field   4x4 matrix representing the puzzle grid.
 * @param left    Array of 4 integers with left-side constraints.
 * @param right   Array of 4 integers with right-side constraints.
 *
 * @return 1 if the field satisfies all puzzle rules, 0 otherwise.
 *
 * Validation steps:
 *   - Rows contain no duplicate values.
 *   - Columns contain no duplicate values.
 *   - Left-right visibility constraints are respected
 *     (applied to the transposed field).
 */
int	field_is_a_solution(int field[4][4], int *left, int *right)
{
	int	transposed[4][4];

	if (!no_duplicates_in_rows(field))
		return (0);
	if (!no_duplicates_in_columns(field))
		return (0);
	transpose_the_field(field, transposed);
	if (!verification_left_right(transposed, left, right))
		return (0);
	return (1);
}

/**
 * Accept and display a valid solution.
 *
 * @param field        4x4 matrix representing the puzzle grid.
 * @param constraints  Array of 4 int* arrays: {top, bottom, left, right}.
 *
 * @return 1 if the field is a valid solution (displayed to stdout),
 *         0 otherwise.
 */
static int	accept(int field[4][4], int **constraints)
{
	if (field_is_a_solution(field, constraints[2], constraints[3]))
	{
		display_field(field);
		return (1);
	}
	return (0);
}

/**
 * Recursive backtracking solver for the Skyscraper puzzle.
 *
 * @param field        4x4 matrix representing the puzzle grid(partial solution).
 * @param row          Current row index being filled.
 * @param constraints  Array of 4 int* arrays: {top, bottom, left, right}.
 *
 * @return 1 if a complete valid solution is found,
 *         0 otherwise.
 *
 * Process:
 *   - For the current column, generate all valid permutations
 *     using the corresponding top/bottom constraints.
 *     (NB! We work in the transposed field and write 'row' while
 *     actually it is a column)
 *   - Fill the 'row' (column) with each candidate permutation.
 *   - Recursively attempt to solve the next row.
 *   - If 'row' == 4, the solution is validated and accepted.
 */
int	solve(int field[4][4], int row, int **constraints)
{
	int	i;
	int	len_row;
	int	arrays[24][4];

	if (row == 4)
		return (accept(field, constraints));
	get_arrays(constraints[0][row], constraints[1][row], arrays);
	len_row = len(constraints[0][row], constraints[1][row]);
	i = 0;
	while (i < len_row)
	{
		fill_row(field, row, arrays, i);
		if (solve(field, row + 1, constraints))
			return (1);
		i++;
	}
	return (0);
}

/**
 * Entry point for solving the puzzle.
 *
 * @param top     Array of 4 integers with top constraints.
 * @param bottom  Array of 4 integers with bottom constraints.
 * @param left    Array of 4 integers with left constraints.
 * @param right   Array of 4 integers with right constraints.
 *
 * @return Pointer to the solved 4x4 field (static storage).
 *
 * This function sets up constraints, runs the recursive solver,
 * and prints either the solution or "Error" if unsolvable.
 */
int	(*find_solution(int *top, int *bottom, int *left, int *right))[4]
{
	static int	field[4][4];
	int			*constraints[4];

	constraints[0] = top;
	constraints[1] = bottom;
	constraints[2] = left;
	constraints[3] = right;
	if (solve(field, 0, constraints))
		return (field);
	write(1, "Error\n", 6);
	return (field);
}

// int	(*find_solution(int *top, int *bottom, int *left, int *right))[4]
// {
// 	static int	field[4][4];
// 	int			r0;
// 	int			r1;
// 	int			r2;
// 	int			r3;
// 	r0 = 0;
// 	while (r0 < len(top[0], bottom[0]))
// 	{
// 		r1 = 0;
// 		while (r1 < len(top[1], bottom[1]))
// 		{
// 			r2 = 0;
// 			while (r2 < len(top[2], bottom[2]))
// 			{
// 				r3 = 0;
// 				while (r3 < len(top[3], bottom[3]))
// 				{
// 					fill_row(field, 0, get_arrays(top[0], bottom[0]), r0);
// 					fill_row(field, 1, get_arrays(top[1], bottom[1]), r1);
// 					fill_row(field, 2, get_arrays(top[2], bottom[2]), r2);
// 					fill_row(field, 3, get_arrays(top[3], bottom[3]), r3);
// 					if (field_is_a_solution(field, left, right))
// 					{
// 						display_field(field);
// 						return (field);
// 					}
// 					r3++;
// 				}
// 				r2++;
// 			}
// 			r1++;
// 		}
// 		r0++;
// 	}
// 	write(1, "Error\n", 6);
// 	return (field);
// }

/**
 * Program entry point.
 *
 * @param argc  Number of arguments.
 * @param argv  Argument vector. Expected: one string containing 16 numbers
 *              (1–4) separated by spaces,
 *              e.g. "2 1 4 2 2 3 1 3 2 3 1 2 2 1 3 2".
 *
 * @return 0 always.
 *
 * Process:
 *   - Validate input format.
 *   - Parse constraints into arrays: top, bottom, left, right.
 *   - Check for contradictions in border constraints.
 *   - Run solver and display solution or "Error".
 */
int	main(int argc, char **argv)
{
	int		*top;
	int		*bottom;
	int		*left;
	int		*right;

	if (argc == 2)
	{
		if (validate_input_condition(argv[1]) == 1)
		{
			top = grab_ints_from_str(argv[1], 0);
			bottom = grab_ints_from_str(argv[1], 8);
			left = grab_ints_from_str(argv[1], 16);
			right = grab_ints_from_str(argv[1], 24);
			if (validate_border_conditions(top, bottom, left, right) != 1)
				write(1, "Error\n", 7);
			else
				find_solution(top, bottom, left, right);
		}
		else
			write(1, "Error\n", 7);
	}
	else
		write(1, "Error\n", 7);
	return (0);
}
