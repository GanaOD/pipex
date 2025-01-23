/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:06:58 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 13:00:29 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stddef.h>
// size_t	ft_strlen(const char	*str);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);

char	*ft_strdup(const char *str_orig)
{
	char	*str_copy;
	int		size_str;

	size_str = ft_strlen(str_orig);
	str_copy = malloc(size_str + 1);
	if (str_copy != NULL)
		ft_strlcpy(str_copy, str_orig, size_str + 1);
	else
		return (NULL);
	return (str_copy);
}

// void	ft_strdup_test(const char *str_orig)
// {
// 	printf("ft_strdup result: %s\n", ft_strdup(str_orig));
// 	printf("Standard library strdup result: %s\n", strdup(str_orig));
// }
// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);
// 	ft_strdup_test(argv[1]);
// 	return (0);
// }