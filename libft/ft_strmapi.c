/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:52:11 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/01 13:00:02 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strmapi(char const *source,
	char (*generic_function)(unsigned int, char))
{
	int		len_str;
	char	*final_str;

	len_str = 0;
	if ((!source) || (generic_function == NULL))
		return (NULL);
	while (source[len_str])
	{
		len_str++;
	}
	final_str = malloc((len_str + 1) * sizeof(char));
	if (!final_str)
		return (NULL);
	len_str = 0;
	while (source[len_str])
	{
		final_str[len_str] = generic_function(
				(unsigned int)len_str, source[len_str]);
		len_str++;
	}
	final_str[len_str] = '\0';
	return (final_str);
}

// char	change_case_of_even_indices_function(unsigned int index,
//	char char_to_convert)
// {
// 	if (index % 2 == 0)
// 	{
// 		if (char_to_convert >= 'a' && char_to_convert <= 'z')
// 			return (char_to_convert - ('a' - 'A'));
// 		else if (char_to_convert >= 'A' && char_to_convert <= 'Z')
// 			return (char_to_convert + ('a' - 'A'));
// 	}
// 	return (char_to_convert);
// }

// void	print_and_free_test_result(char *test_name, char const *source)
// {
// 	char	*final_str;

// 	final_str = ft_strmapi(source, change_case_of_even_indices_function);
// 	printf("\nTest: %s\n", test_name);
// 	printf("Source str: %s\n", source);
// 	printf("Result: %s\n", final_str);
// 	free(final_str);
// }

// int	main(void)
// {
// 	print_and_free_test_result("Basic use - lowercase string", "hello");
// 	print_and_free_test_result("Basic use - uppercase string", "HELLO");
// 	print_and_free_test_result("Basic use - mixed case string", "HeLLo");
// 	print_and_free_test_result("Edge case - empty string", "");
// 	print_and_free_test_result("Edge case - single character", "a");
// 	print_and_free_test_result("Error case - NULL string", NULL);
// 	print_and_free_test_result("Special chars - punctuation and spaces",
//	"Hello, World!");
// 	print_and_free_test_result("Special chars - numbers", "Hello123World");
// }
