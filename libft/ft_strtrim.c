/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:37:02 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/28 12:45:28 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

// size_t	ft_strlen(const char	*str);
// char	*ft_strchr(const char *src, int c);

// Finds start & end positions for trimmed str
// Returns 1 if entire str to be trimmed, else 0

static int	get_trim_bounds(char const *s1, char const *set,
	size_t *start, size_t *end)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	*start = i;
	if (i == len)
		return (1);
	i = len - 1;
	while (i > *start && ft_strchr(set, s1[i]))
		i--;
	*end = i;
	return (0);
}

// Allocate & create trimmed str
// Return NULL if allocation fails

static char	*create_trimmed_str(char const *s1, size_t start, size_t end)
{
	char	*trimmed;
	size_t	len;

	len = (end - start) + 1;
	trimmed = (char *)malloc((len + 1) * sizeof(char));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, len + 1);
	return (trimmed);
}

// creates an empty str
// returns NULL if allocation fails
// needed later if get_trim_bounds returns 1
static char	*create_empty_str(void)
{
	char	*trimmed;

	trimmed = (char *)malloc(1);
	if (!trimmed)
		return (NULL);
	trimmed[0] = '\0';
	return (trimmed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	if (get_trim_bounds(s1, set, &start, &end))
		return (create_empty_str());
	return (create_trimmed_str(s1, start, end));
}

// prints test details & results:

// static void	print_test_result(char const *test_name, const char *s1,
// 	const char *set, const char *expected, char *result)
// {
// 	printf("\nTest: %s\n", test_name);
// 	printf("Input string: %s\n", s1 ? s1 : "NULL");
// 	printf("Set to trim: %s\n", set ? set : "NULL");
// 	printf("Expected: %s\n", expected ? expected : "NULL");
// 	printf("Got: %s\n", result ? result : "NULL");
// }

// int	main(void)
// {
// 	char	*result;

// 	// Basic functionality tests
// 	result = ft_strtrim("SwissMountains", "Swiss");
// 	print_test_result("Basic trim at start", "SwissMountains", "Swiss",
// 		"Mountains", result);
// 	free (result);

// 	result = ft_strtrim("   hello   ", " ");
//     print_test_result("Whitespace trim", "   hello   ", " ", 
//                      "hello", result);
//     free(result);

//     // Edge cases
//     result = ft_strtrim("", "abc");
//     print_test_result("Empty string", "", "abc", 
//                      "", result);
//     free(result);

//     // Error handling
//     result = ft_strtrim(NULL, "abc");
//     print_test_result("NULL string", NULL, "abc", 
//                      NULL, result);

//     return (0);
// }