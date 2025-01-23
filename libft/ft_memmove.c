/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:09:13 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/22 12:57:17 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memmove_forward(unsigned char *dest,
	const unsigned char *src, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
}

static void	ft_memmove_backward(unsigned char *dest,
	const unsigned char *src, size_t length)
{
	while (length > 0)
	{
		length--;
		dest[length] = src[length];
	}
}

void	*ft_memmove(void *destination, const void *source, size_t length)
{
	unsigned char		*dest;
	const unsigned char	*src;

	dest = (unsigned char *)destination;
	src = (const unsigned char *)source;
	if (dest == src)
		return (destination);
	if (dest < src)
		ft_memmove_forward(dest, src, length);
	if (dest > src)
		ft_memmove_backward(dest, src, length);
	return (destination);
}
