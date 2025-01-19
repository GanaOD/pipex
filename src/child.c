/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:43:13 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/19 13:48:50 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_second_child(t_pipex *pipex)
{
	// 2nd child needs: pipe read > stdin, outfile > stdout

	// // Open outfile
    // pipex->outfile = safe_open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (pipex->outfile == -1)
	// 	exit_error("Outfile error");


	// DEBUGGING
	ft_putstr_fd("\n--- Second Child Process ---\n", 2);
    pipex->outfile = safe_open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile != -1)
        ft_putstr_fd("Outfile opened successfully\n", 2);
    else
        ft_putstr_fd("Failed to open outfile\n", 2);




	// Try to create/open outfile
    pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
    {
        // Print error in shell format and exit
        ft_putstr_fd("pipex: ", 2);
        perror(pipex->argv[4]);
        exit(EXIT_FAILURE);
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


	// DEBUGGING
	ft_putstr_fd("Executing command: ", 2);
    ft_putstr_fd(pipex->cmd2.raw_cmd, 2);
    ft_putstr_fd("\n", 2);


    execute_command(&pipex->cmd2, pipex->envp);
}

void handle_first_child(t_pipex *pipex)
{
	// 1st child needs: infile > stdin & pipe write > stdout

	// // Open input file
    // pipex->infile = open(pipex->argv[1], O_RDONLY, 0644);
    // if (pipex->infile == -1)
	// {
	// 	ft_putstr_fd("pipex: ", 2);
    //     perror(pipex->argv[1]);
	// }

	// DEBUGGING:
	ft_putstr_fd("\n--- First Child Process ---\n", 2);
	pipex->infile = open(pipex->argv[1], O_RDONLY, 0644);
	if (pipex->infile != -1)
        ft_putstr_fd("Infile opened successfully\n", 2);
    else
        ft_putstr_fd("Failed to open infile\n", 2);



	// Close unused read end copy before redirecting output
	safe_close(pipex->pipe[0]);


	// Redirect stdin > infile (if open) or keep stdin if file failed to open
	if (pipex->infile != -1)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to infile");
	}


	// Redirect stdout > pipe write end
	if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to pipe");

	// DEBUGGING
	ft_putstr_fd("Executing command: ", 2);
    ft_putstr_fd(pipex->cmd1.raw_cmd, 2);
    ft_putstr_fd("\n", 2);


	// Close remaining fds
	if (pipex->infile != -1)
		safe_close(pipex->infile);
	safe_close(pipex->pipe[1]);

	// Execute 1st command
	// Will fail if infile couldn't be opened (expected behaviour)
    execute_command(&pipex->cmd1, pipex->envp);
}

// Uses open, not safe_open for more nuanced error handling: instead of immediately exiting on error (can easily happen with file1, process 1 / cmd1), want to: report error, continue execution & handle failed fd in process flow
