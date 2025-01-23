/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 07:32:34 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/01 08:50:56 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static int	count_digits(int int_input)
{
	int	int_len;

	int_len = 0;
	if (int_input == 0)
		return (1);
	if (int_input < 0)
		int_len++;
	while (int_input != 0)
	{
		int_input = (int_input / 10);
		int_len++;
	}
	return (int_len);
}

static char	*convert_int_digits_to_str(char *created,
	int int_input, int int_len)
{
	int	is_negative_boolean_flag;

	is_negative_boolean_flag = 0;
	if (int_input < 0)
	{
		created[0] = '-';
		is_negative_boolean_flag = 1;
		int_input = -int_input;
	}
	created[int_len] = '\0';
	while (int_len > is_negative_boolean_flag)
	{
		int_len--;
		created[int_len] = (int_input % 10) + '0';
		int_input = (int_input / 10);
	}
	return (created);
}

char	*ft_itoa(int int_input)
{
	int		int_len;
	char	*final_str;

	if (int_input == -2147483648)
		return (ft_strdup("-2147483648"));
	int_len = count_digits(int_input);
	final_str = malloc((int_len + 1) * sizeof(char));
	if (!final_str)
		return (NULL);
	return (convert_int_digits_to_str(final_str, int_input, int_len));
}

// static void	print_test_final_str(const char *test_name,
//	int int_input, char *final_str)
// {
// 	printf("Test name: %s\n", test_name);
// 	printf("Input: %d\n", int_input);
// 	printf("Output: %s\n", final_str);
// }

// int	main(void)
// {
// 	char	*final_str;

// 	/* 1. Basic Functionality Tests */
//     // Simple positive
//     final_str = ft_itoa(42);
//     print_test_final_str("Basic Positive", 42, final_str);
//     free(final_str);

//     // Simple negative
//     final_str = ft_itoa(-42);
//     print_test_final_str("Basic Negative", -42, final_str);
//     free(final_str);

//     // Zero
//     final_str = ft_itoa(0);
//     print_test_final_str("Zero", 0, final_str);
//     free(final_str);

//     /* 2. Edge Cases */
//     // Maximum integer
//     final_str = ft_itoa(2147483647);
//     print_test_final_str("INT_MAX", 2147483647, final_str);
//     free(final_str);

//     // Minimum integer
//     final_str = ft_itoa(-2147483648);
//     print_test_final_str("INT_MIN", -2147483648, final_str);
//     free(final_str);

// 	return (0);
// }
