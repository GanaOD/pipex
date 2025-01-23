/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:59:38 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 12:59:59 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	*ft_memset(void *destination, int fill_value, size_t byte_count)
{
	unsigned char	*memory_ptr;
	unsigned char	fill_char;
	size_t			index;

	memory_ptr = (unsigned char *)destination;
	fill_char = (unsigned char)fill_value;
	index = 0;
	while (index < byte_count)
	{
		memory_ptr[index] = fill_char;
		index++;
	}
	return (destination);
}

// int main()
// {
//     char            destination[21];
//     int             fill_value;
//     unsigned int    byte_count;

//     char init_string[] = "Hello, World!";
//     unsigned int i = 0;
//     while (init_string[i] != '\0' && i < 20)
//     {
//         destination[i] = init_string[i];
//         i++;
//     }
//     destination[i] = '\0'; 

//     fill_value = 'g';
//     byte_count = 5;

//     printf("Before: %s\n", destination);
//     ft_memset(destination, fill_value, byte_count);
//     printf("After: %s\n", destination);
//     return (0);
// }