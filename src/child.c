/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:43:13 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/25 10:35:26 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_infile_error(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	if (errno == EACCES)
		ft_putstr_fd("permission denied: ", 2);
	else if (errno == ENOENT)
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
	exit(1);
}

void	handle_first_child(t_pipex *pipex)
{
	int	exit_code;

	pipex->infile = safe_open(pipex->argv[1], O_RDONLY, 0644);
	if (pipex->infile == -1)
		handle_infile_error(pipex->argv[1]);
	safe_close(pipex->pipe[0]);
	if (pipex->infile != -1)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			exit_error("Failed to redirect stdin to infile");
	}
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to pipe");
	if (pipex->infile != -1)
		safe_close(pipex->infile);
	safe_close(pipex->pipe[1]);
	exit_code = execute_first_command(&pipex->cmd1, pipex->envp);
	cleanup_pipex(pipex);
	exit(exit_code);
}

void	handle_second_child(t_pipex *pipex)
{
	pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		if (errno == EACCES)
			ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(pipex->argv[4], 2);
		exit(1);
	}
	safe_close(pipex->pipe[1]);
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to pipe");
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to output file");
	safe_close(pipex->pipe[0]);
	safe_close(pipex->outfile);
	execute_second_command(&pipex->cmd2, pipex->envp);
}
