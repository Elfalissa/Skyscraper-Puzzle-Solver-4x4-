/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skyscraper.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisamanukhova <alisamanukhova@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:17:49 by alisamanukh       #+#    #+#             */
/*   Updated: 2025/09/02 20:32:02 by alisamanukh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYSCRAPER_H
# define SKYSCRAPER_H
# include <unistd.h>
# include <stdlib.h>

///////////////////////////////////
//Helping functions for get_arrays
///////////////////////////////////

int		count_visible(int arr[4]);
void	reverse(int src[4], int dest[4]);
void	swap(int *a, int *b);
int		has_duplicate(int arr[], int l, int i);
void	save_result(int arr[], void *ctx[4]);
void	permute(int arr[], int l, int r, void *ctx[4]);
void	clear_tail(int result[24][4], int start);
// int		(*get_arrays(int a, int b))[4];

///////////////////////////////////
//Validations
///////////////////////////////////

int		validate_input_condition(char *str);
int		validate_border_conditions(int *up, int *down, int *left, int *right);
int		no_duplicates_in_columns(int field[4][4]);
int		no_duplicates_in_rows(int field[4][4]);
int		verification_left_right(int field[4][4], int *left, int *right);
int		verification_left_right(int field[4][4], int *left, int *right);

///////////////////////////////////
//Helpers
///////////////////////////////////

void	write_number(int n);
void	display_field(int field[4][4]);
int		is_presented(int *s1, int *s2);

///////////////////////////////////
//Field Helpers
///////////////////////////////////

void	transpose_the_field(int src[4][4], int dest[4][4]);
void	fill_row(int field[4][4], int row, int (*arrays)[4], int idx);
int		*grab_ints_from_str(char *str, int start);

//////////////////////////////////
//get_arrays
///////////////////////////////////

void	get_arrays(int a, int b, int result[24][4]);
int		len(int a, int b);

#endif