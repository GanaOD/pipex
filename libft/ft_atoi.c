/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:06:48 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/27 13:14:43 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>

static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
		if (**str == '+' || **str == '-')
			return (0);
	}
	return (sign);
}

static int	check_overflow(int result, char digit)
{
	if (result > INT_MAX / 10)
		return (1);
	else if (result == INT_MAX / 10 && digit - '0' > INT_MAX % 10)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = handle_sign(&str);
	if (sign == 0)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		if (check_overflow(result, *str))
		{
			if (sign == 1)
				return (INT_MAX);
			else if (sign == -1)
				return (INT_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <string_to_convert>\n", argv[0]);
// 		return (1);
// 	}
// 	printf("Input string: %s\n", argv[1]);
// 	printf("ft_atoi result: %d\n", ft_atoi(argv[1]));
// 	printf("stdlib atoi result: %d\n", atoi(argv[1]));

// 	return(0);
// }
