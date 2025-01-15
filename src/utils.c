/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:05:16 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 17:58:24 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Error handling and cleanup utilities for pipex
*/

#include "pipex.h"

void	ft_free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// freeing memory malloced by ft_split
// Setting freed pointers to NULL: defensive programming, preventing "dangling pointers"
void	cleanup_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return;

	// Free argument array and its contents
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		cmd->args = NULL;
	}

	// Free command path if allocated
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}

	// Don't free raw_cmd as it points to argv
	cmd->raw_cmd = NULL;
}

int	error_handler(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

void	exit_error(char *msg)
{
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}
