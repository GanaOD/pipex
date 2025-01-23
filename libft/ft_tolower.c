/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:56:09 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 13:03:15 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + ('a' - 'A'));
	}
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int	main()
// {
// 	int	test_value;

// 	test_value = 74;

// 	printf("Input value: %d\n", test_value);
// 	printf("Input as char: %c\n", test_value);
// 	printf("After conversion as value: %d\n", ft_tolower(test_value));
// 	printf("After conversion as char: %c\n", ft_tolower(test_value));
// 	printf("Output int with standard tolower: %d\n", tolower(test_value));
// 	printf("Output char with standard tolower: %c\n", tolower(test_value));

// 	return(0);
// }