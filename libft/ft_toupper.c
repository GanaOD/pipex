/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:13:37 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 13:03:40 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - ('a' - 'A'));
	}
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>

// int main(void)
// {
//     int test_value;

//     test_value = 101;

//     printf("Testing ft_toupper with value: %d\n", test_value);
//     printf("Character representation: '%c'\n", test_value);
//     printf("ft_toupper result: %d\n", ft_toupper(test_value));
//     printf("ft_toupper character: '%c'\n", ft_toupper(test_value));
//     printf("Standard toupper result: %d\n", toupper(test_value));
//     printf("Standard toupper character: '%c'\n", toupper(test_value));

//     return (0);
// }