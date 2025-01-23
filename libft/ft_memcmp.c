/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:27:41 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 12:57:02 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stddef.h>
// #include <stdio.h>
// #include <string.h>

int	ft_memcmp(const void *m1, const void *m2, size_t size)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	size_t				i;

	p1 = (const unsigned char *)m1;
	p2 = (const unsigned char *)m2;
	i = 0;
	while (i < size)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

// int	memcmp(const void *m1, const void *m2, size_t size);

// int	test_ft_memcmp(const void *m1, const void *m2, 
// size_t size, const char *test_name)
// {
// 	int	result;
// 	int	expected;

// 	result = ft_memcmp(m1, m2, size);
// 	expected = memcmp(m1, m2, size);

// 	printf("Test: %s\n", test_name);
// 	printf("ft_memcmp result:	%d\n", result);
// 	printf("memcmp result:		%d\n", expected);
// 	printf("Test %s\n\n", (result == expected) ? "PASSED" : "FAILED");

// 	return (result == expected);
// }

// int	main()
// {
// 	const char	*m1;
// 	const char	*m2;
// 	size_t		size;

// 	m1 = "Hello, World!";
// 	m2 = "Hello, Werld!";
// 	size = 13;

// 	test_ft_memcmp(m1, m2, size, "Normal case");

// 	test_ft_memcmp("abcde", "abcde", 5, "Identical strings");
//     test_ft_memcmp("abcde", "abcdf", 5, "Difference at end");
//     test_ft_memcmp("abcde", "abcde", 3, "Partial comparison");
//     test_ft_memcmp("\200", "\0", 1, "Unsigned char comparison");

// 	return (0);
// }