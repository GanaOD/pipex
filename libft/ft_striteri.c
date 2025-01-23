/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:10:21 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/01 15:34:27 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *str, void (*choose_a_function)(unsigned int, char*))
{
	unsigned int	index;

	index = 0;
	if (!str || !choose_a_function)
		return ;
	while (str[index] != '\0')
	{
		choose_a_function(index, &str[index]);
		index++;
	}
}
