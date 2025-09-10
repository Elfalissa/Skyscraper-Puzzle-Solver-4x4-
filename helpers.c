/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:07:47 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/05 16:12:22 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skyscraper.h"

/**
 * Swap the values of two integers.
 *
 * @param a  Pointer to the first integer.
 * @param b  Pointer to the second integer.
 *
 * After execution, the values at *a and *b are exchanged.
 */
void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * Reverse the contents of a 4-element array.
 *
 * @param src   Source array of 4 integers.
 * @param dest  Destination array of 4 integers.
 *
 * Copies src into dest in reversed order.
 *
 * Example:
 *   src  = {2, 3, 4, 1}
 *   dest = {1, 4, 3, 2}
 */
void	reverse(int src[4], int dest[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		dest[i] = src[3 - i];
		i++;
	}
}

/**
 * Write an integer to standard output.
 *
 * @param n  The integer to write.
 *
 * This function recursively breaks the number into digits
 * and writes them as characters using the write system call.
 * Only positive integers are expected in this project.
 */
void	write_number(int n)
{
	char	c;

	if (n >= 10)
		write_number(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
}

/**
 * Display a 4x4 skyscraper field on the terminal.
 *
 * @param field  A 4x4 matrix of integers representing skyscraper heights.
 *
 * The field is printed row by row, with numbers separated by spaces.
 * Each row ends with a newline.
 * NB! here we finally transpose the field back, so 'row' is a column
 *
 * Example output:
 *   1 2 3 4
 *   2 3 4 1
 *   3 4 1 2
 *   4 1 2 3
 */
void	display_field(int field[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			write_number(field[j][i]);
			if (j < 3)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

/**
 * Compare two 4-element arrays for equality.
 *
 * @param s1  First array of 4 integers.
 * @param s2  Second array of 4 integers.
 *
 * @return    1 if the arrays are identical element by element,
 *            0 otherwise.
 *
 * This is used to check whether a row in the field matches
 * one of the valid row permutations.
 */
int	is_presented(int *s1, int *s2)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
