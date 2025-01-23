/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:48:40 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/26 15:03:34 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdlib.h>
// #include <stdio.h>

size_t	ft_strlen(const char *s);

static size_t	ft_get_total_len(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (!s2)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len;
	return (total_len);
}

static void	ft_copy_strings(char *final_str, const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		final_str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		final_str[j] = s2[i];
		i++;
		j++;
	}
	final_str[j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	size_t	total_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	total_len = ft_get_total_len(s1, s2);
	final_str = (char *)malloc((total_len + 1) * sizeof(char));
	if (!final_str)
		return (NULL);
	ft_copy_strings(final_str, s1, s2);
	return (final_str);
}

// void	test_strjoin(const char *s1, const char *s2, 
//     const char *test_name, const char *expected)
// {
//     char	*result;

//     printf("\nTest: %s\n", test_name);

//     if (s1)
//         printf("s1: %s\n", s1);
//     else
//         printf("s1: NULL\n");

//     if (s2)
//         printf("s2: %s\n", s2);
//     else
//         printf("s2: NULL\n");

//     printf("Expected: %s\n", expected);

//     result = ft_strjoin(s1, s2);
//     if (result)
//         printf("Result: %s\n", result);
//     else
//         printf("Result: NULL\n");

//     if (result)
//         free(result);
// }

// int	main(void)
// {
//     test_strjoin(
//         "Two roads diverged in a ",
//         "yellow wood",
//         "Frost's Roads",
//         "Two roads diverged in a yellow wood"
//     );

//     test_strjoin(
//         "Shall I compare thee ",
//         "to a summer's day?",
//         "Shakespeare's Summer",
//         "Shall I compare thee to a summer's day?"
//     );

//     test_strjoin(
//         "",
//         "Nevermore!",
//         "Empty + Word",
//         "Nevermore!"
//     );

//     test_strjoin(
//         "Quoth the Raven: ",
//         "",
//         "Word + Empty",
//         "Quoth the Raven: "
//     );

//     test_strjoin(
//         NULL,
//         "I contain multitudes.",
//         "NULL + Line",
//         "I contain multitudes."
//     );

//     test_strjoin(
//         "l(a\n",
//         "le\taf\nfa)ll\ns",
//         "Special Characters",
//         "l(a\nle\taf\nfa)ll\ns"
//     );

//     return (0);
// }