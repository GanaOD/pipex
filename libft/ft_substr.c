/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:14:56 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/27 13:02:39 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

static size_t	calculate_substr_size(size_t orig_len,
	unsigned int start, size_t len)
{
	size_t	actual_len;

	if (start >= orig_len)
		return (1);
	actual_len = orig_len - start;
	if (actual_len > len)
		actual_len = len;
	return (actual_len + 1);
}

static void	copy_substr(char *dest, const char *src,
	unsigned int start, size_t size)
{
	size_t	i;

	i = 0;
	while (i < (size - 1))
	{
		dest[i] = src[start + i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_substr(char const *orig, unsigned int start, size_t len)
{
	char	*substr;
	size_t	orig_len;
	size_t	size;

	if (!orig)
		return (NULL);
	orig_len = ft_strlen(orig);
	size = calculate_substr_size(orig_len, start, len);
	substr = malloc(size);
	if (!substr)
		return (NULL);
	copy_substr(substr, orig, start, size);
	return (substr);
}

// void	print_test(const char *test_name, const char *orig, 
// 		unsigned int start, size_t len, const char *expected)
// {
// 	char	*result;
// 	char	*status;

// 	printf("Test: %s\n", test_name);
// 	printf("Input: \"%s\", start: %u, len: %zu\n", orig, start, len);
// 	printf("Expected: \"%s\"\n", expected);
// 	result = ft_substr(orig, start, len);
// 	if (result)
// 		printf("Got: \"%s\"\n", result);
// 	else
// 		printf("Got: NULL\n");

// 	if (result && strcmp(result, expected) == 0)
// 		status = "PASS";
// 	else
// 		status = "FAIL";
// 	printf("Result:  %s\n\n", status);
// 	free(result);
// }

// int	main(void)
// {
// 	// Basic functionality tests
// 	print_test("Basic substring", "Hello World", 6, 3, "Wor");
// 	print_test("Full string", "Hello", 0, 5, "Hello");
// 	print_test("Empty length", "Hello", 0, 0, "");
// 	// Edge cases
// 	print_test("NULL input", NULL, 0, 5, "");
// 	print_test("Start beyond string", "Hello", 10, 5, "");
// 	print_test("Length beyond string", "Hello", 0, 10, "Hello");
// 	print_test("Start at end", "Hello", 5, 5, "");
// 	// Boundary tests
// 	print_test("One char", "Hello", 1, 1, "e");
// 	print_test("Last char", "Hello", 4, 1, "o");
// 	// Memory tests (look for leaks)
// 	print_test("Large length", "Hi", 0, 1000000, "Hi");
// 	print_test("Empty string", "", 0, 5, "");
// 	return (0);
// }