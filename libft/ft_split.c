/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:47:57 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/01 07:31:28 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stddef.h>
#include "libft.h"

//2. Navigation: find next substr
//state flag: 1 = in a substr, 0 = in delim
static const char	*find_next_substr(const char *str, char delim)
{
	while (*str && (*str == delim))
		str++;
	return (str);
}

// 3. Calculate len of substr then extract (allocate & copy)
static char	*get_next_substr(const char *new_substr, char delim, size_t *len)
{
	size_t	copy_index;
	char	*extracted;

	*len = 0;
	copy_index = 0;
	while (new_substr[*len] && (new_substr[*len] != delim))
		(*len)++;
	extracted = malloc((*len + 1) * sizeof(char));
	if (!extracted)
		return (NULL);
	while (copy_index < *len)
	{
		extracted[copy_index] = new_substr[copy_index];
		copy_index++;
	}
	extracted[*len] = '\0';
	return (extracted);
}

// 4. Cleanup helper for error cases, e.g. partial allocation
static void	free_array(char **final_array, size_t count)
{
	size_t	array_index;

	array_index = 0;
	while (array_index < count)
	{
		free(final_array[array_index]);
		array_index++;
	}
	free (final_array);
}

//5. Create final_array
// static char	**create_final_empty_array(void)
// {
// 	char	**final_array;
// 	final_array = malloc(2 * sizeof(char *));
// 	if (!final_array)
// 		return (NULL);
// 	final_array[0] = get_next_substr_substr("", 0);
// 	if (!final_array[0])
// 	{
// 		free_array(final_array, 0);
// 		return (NULL);
// 	}
// 	final_array[1] = NULL;
// 	return (final_array);
// }
static char	**create_final_array(const char *str,
	char delim, size_t substr_count)
{
	char		**final_array;
	size_t		array_index;
	const char	*substr_start;
	size_t		len;

	array_index = 0;
	final_array = malloc((substr_count + 1) * sizeof(char *));
	if (!final_array)
		return (NULL);
	substr_start = find_next_substr(str, delim);
	while (array_index < substr_count)
	{
		final_array[array_index] = get_next_substr(substr_start, delim, &len);
		if (!final_array[array_index])
		{
			free_array(final_array, array_index);
			return (NULL);
		}
		substr_start = find_next_substr(substr_start + len, delim);
		array_index++;
	}
	final_array[substr_count] = NULL;
	return (final_array);
}

// 1. ft_split
char	**ft_split(const char *str, char delim)
{
	size_t		substr_count;
	int			in_word;
	const char	*str_start;

	substr_count = 0;
	in_word = 0;
	str_start = str;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == delim)
			in_word = 0;
		else if ((*str != delim) && (in_word == 0))
		{
			in_word = 1;
			substr_count++;
		}
		str++;
	}
	return (create_final_array(str_start, delim, substr_count));
}
