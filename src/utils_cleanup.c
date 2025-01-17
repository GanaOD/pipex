/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:04:28 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/17 19:05:25 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void cleanup_pipex(t_pipex *pipex)
{
	if (!pipex)
		return;

	// Close file descriptors if open
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pipe[0] != -1)
		close(pipex->pipe[0]);
	if (pipex->pipe[1] != -1)
		close(pipex->pipe[1]);

	// Cleanup commands
	cleanup_command(&pipex->cmd1);
	cleanup_command(&pipex->cmd2);

	// Reset all pointers and file descriptors
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;
	pipex->envp = NULL;  // Don't free as it's from main
}
