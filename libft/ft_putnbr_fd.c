/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:27:28 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/02 15:07:30 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int number, int filedescr)
{
	if (number == -2147483648)
	{
		ft_putstr_fd("-2147483648", filedescr);
		return ;
	}
	if (number < 0)
	{
		ft_putchar_fd('-', filedescr);
		number = -number;
	}
	if (number >= 10)
		ft_putnbr_fd(number / 10, filedescr);
	ft_putchar_fd((number % 10) + '0', filedescr);
}
