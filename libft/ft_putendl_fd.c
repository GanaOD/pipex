/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:30:37 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/02 13:22:37 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fildes)
{
	size_t	len;
	ssize_t	bytes_written;
	char	nl;

	if (!str || fildes < 0 || fildes >= 1024)
		return ;
	len = ft_strlen(str);
	nl = '\n';
	bytes_written = write(fildes, str, len);
	if (bytes_written == -1)
		return ;
	bytes_written = write(fildes, &nl, 1);
}
