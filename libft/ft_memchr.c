/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:33:48 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 12:56:10 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>
// #include <limits.h>
// #include <stdint.h>

void	*ft_memchr(const void *memory, int search_byte, size_t num_bytes)
{
	const unsigned char	*memory_ptr;
	unsigned char		target;

	memory_ptr = memory;
	target = search_byte;
	while (num_bytes--)
	{
		if (*memory_ptr == target)
			return ((void *)memory_ptr);
		memory_ptr++;
	}
	return (NULL);
}

// void *ft_memchr(const void *memory, int search_byte, size_t num_bytes);

// void test_ft_memchr(const void *s, int c, size_t n, const char *test_name) {
//     void *result = ft_memchr(s, c, n);
//     void *expected = memchr(s, c, n);
//     printf("Test: %s\n", test_name);
//     printf("ft_memchr result: %p\n", result);
//     printf("memchr result:    %p\n", expected);
//     printf("Test %s\n\n", (result == expected) ? "PASSED" : "FAILED");
// }

// int main() {
//     // Normal case
//     char str[] = "Hello, World!";
//     test_ft_memchr(str, 'o', strlen(str), "Normal case");

//     // Edge case - first character
//     test_ft_memchr(str, 'H', strlen(str), "Edge case - first character");

//     // Edge case - last character
//     test_ft_memchr(str, '!', strlen(str), "Edge case - last character");

//     // Character not in string
//     test_ft_memchr(str, 'z', strlen(str), "Character not in string");

//     // Empty string
//     test_ft_memchr("", 'a', 0, "Empty string");

//     // Null terminator
//     test_ft_memchr("Hello", '\0', 6, "Null terminator");

//     // Large value for n
//     test_ft_memchr(str, 'o', SIZE_MAX, "Large value for n");

//     // Non-character search
//     test_ft_memchr(str, 256, strlen(str), "Non-character search");

//     // Search in non-string data
//     int arr[] = {1, 2, 3, 4, 5};
//     test_ft_memchr(arr, 3, sizeof(arr), "Search in non-string data");

//     return 0;
// }