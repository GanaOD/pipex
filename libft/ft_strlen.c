/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:44:34 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/01 10:32:21 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stddef.h>

size_t	ft_strlen(const char *str)
{
	const char	*count;

	count = str;
	while (*count)
	{
		count++;
	}
	return (count - str);
}
