/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:43:13 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 11:28:25 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_child(t_pipex *pipex)
{
	int	exit_code;

	// 1st child needs: infile > stdin & pipe write > stdout

	// Open input file
    pipex->infile = safe_open(pipex->argv[1], O_RDONLY, 0644);
    if (pipex->infile == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		if (errno == EACCES) // permission denied error
			ft_putstr_fd("permission denied: ", 2);
		else if (errno == ENOENT)
            ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(pipex->argv[1], 2);
		exit(1); // exit with status 1 like shell
	}

	// Close unused read end copy before redirecting output
	safe_close(pipex->pipe[0]);


	// Set up redirections

	// Redirect stdin > infile (if open) or keep stdin if file failed to open
	if (pipex->infile != -1)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to infile");
	}

	// Redirect stdout > pipe write end
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to pipe");



	// Close remaining fds
	if (pipex->infile != -1)
		safe_close(pipex->infile);
	safe_close(pipex->pipe[1]);


	// Execute 1st command
	// Will fail if infile couldn't be opened (expected behaviour)
    exit_code = execute_first_command(&pipex->cmd1, pipex->envp);

	exit(exit_code);
}

// Uses open, not safe_open for more nuanced error handling: instead of immediately exiting on error (can easily happen with file1, process 1 / cmd1), want to: report error, continue execution & handle failed fd in process flow



void	handle_second_child(t_pipex *pipex)
{
	// 2nd child needs: pipe read > stdin, outfile > stdout

	// Try to create/open outfile
    pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
    {
        // Print error in shell format and exit
        ft_putstr_fd("pipex: ", 2);
		if (errno == EACCES)
			ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(pipex->argv[4], 2); // this function adds newline at end
        exit(1);
    }

	// Close unused write end before redirecting input
	safe_close(pipex->pipe[1]);

	// Redirect stdin to pipe read end
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to pipe");

    // Redirect stdout to outfile
    if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to output file");

    // Close remaining fds
	safe_close(pipex->pipe[0]);
    safe_close(pipex->outfile);

    execute_second_command(&pipex->cmd2, pipex->envp);
}
