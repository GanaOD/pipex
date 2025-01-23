/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:46:39 by go-donne          #+#    #+#             */
/*   Updated: 2024/10/28 12:25:14 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strrchr(const char *src, int c)
{
	const char		*last;
	unsigned char	chr;

	chr = (unsigned char)c;
	last = NULL;
	if (chr == '\0')
	{
		while (*src)
			src++;
		return ((char *)src);
	}
	while (*src)
	{
		if (*src == (char)chr)
			last = src;
		src++;
	}
	return ((char *)last);
}
