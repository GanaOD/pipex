/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:49:21 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/02 10:38:13 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *str, int fildes)
{
	size_t	len;
	ssize_t	bytes_written;

	if (!str || fildes < 0)
		return ;
	len = 0;
	while (str[len])
		len++;
	bytes_written = write(fildes, str, len);
}
