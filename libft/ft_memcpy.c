/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:29:02 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/27 12:35:44 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict destination, const void *restrict source,
	size_t byte_count)
{
	unsigned char		*destination_bytes;
	const unsigned char	*source_bytes;
	size_t				byte_index;

	if (!destination && !source)
		return (destination);
	if (byte_count == 0 || destination == source)
		return (destination);
	destination_bytes = (unsigned char *)destination;
	source_bytes = (const unsigned char *)source;
	byte_index = 0;
	while (byte_index < byte_count)
	{
		destination_bytes[byte_index] = source_bytes[byte_index];
		byte_index++;
	}
	return (destination);
}

// #include <stdio.h>

// int main()
// {
// 	char	source_str[] = "Hello, World";
// 	char	destination_buffer[20];

// 	ft_memcpy(destination_buffer, source_str, 15);

// 	printf("Source string: %s\n", source_str);
// 	printf("Destination buffer: %s\n", destination_buffer);

// 	return (0);
// }