/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:05:16 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/18 15:17:09 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// for validation and logic errors (non-fatal errors)
int	error_handler(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

// for system call failures where errno is set (fatal errors)
void	exit_error(char *msg)
{
	if (msg)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		perror(msg);
		exit(EXIT_FAILURE);
	}
}
