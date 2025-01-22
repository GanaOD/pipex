/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:04:28 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 15:55:58 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Free null-terminated string array
void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// Clean up single command resources (freeing memory malloced by ft_split)
void	cleanup_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	cmd->raw_cmd = NULL;
}

// Clean up all program resources
void	cleanup_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);
	cleanup_command(&pipex->cmd1);
	cleanup_command(&pipex->cmd2);
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;
	pipex->envp = NULL;
}
