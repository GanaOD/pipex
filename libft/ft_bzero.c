/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:14:24 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 12:46:20 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *destination, size_t byte_count)
{
	unsigned char	*memory_ptr;
	size_t			index;

	memory_ptr = (unsigned char *)destination;
	index = 0;
	while (index < byte_count)
	{
		memory_ptr[index] = 0;
		index++;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	destination[20] = "Hello, World";
// 	size_t	byte_count = 5;
// 	printf("Before: %s\n", destination);
// 	ft_bzero(destination, byte_count);

// 	printf("After: ");
// 	for (size_t i = 0; i < 20; i++)
// 	{
// 		if (destination[i] == '\0')
// 			printf("\\0");
// 		else
// 			printf("%c", destination[i]);
// 	}
// 	printf("\n");

// 	return (0);
// }