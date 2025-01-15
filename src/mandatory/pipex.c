/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 16:43:02 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// wrapping dup(2) calls directly in error checks
void handle_child(t_pipex *pipex)
{
	// Open input file
	pipex->infile = safe_open(pipex->argv[1], O_RDONLY);
	if (pipex->infile == -1)
		exit_error("Input file error");

	// Redirect stdin to infile
	if(dup2(pipex->infile, STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to input file");

	// Redirect stdout to pipe
	if(dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to pipe write end");

	// Close unused read end
	if (safe_close(pipex->pipe[0]) == -1)
		exit_error("Failed to close unused pipe read end");

	// Execute first command
	execute_command(&pipex->cmd1, pipex->envp);
}

void handle_parent(t_pipex *pipex)
{
	// Open output file
	pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		exit_error("Output file error");

	// Redirect stdin to pipe
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to pipe read end");

	// Redirect stdout to outfile
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to outfile");

	// Close unused write end
	if (safe_close(pipex->pipe[1]) == -1)
		exit_error("Failed to close unused pipe write end");

	// Execute second command
	execute_command(&pipex->cmd2, pipex->envp);
}

/*
Setting the following pointers to NULL is good practice because:

It gives them a known initial state
We can later check if they're NULL before trying to use them
It helps prevent undefined behavior from uninitialized pointers
Makes it clear these will be allocated/assigned later during command parsing
*/

void    init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	// Initialize file descriptors to -1 (invalid)
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;

	// Store environment variables
	pipex->envp = envp;

	// Initialize first command
	pipex->cmd1.raw_cmd = argv[2];
	// "Store the address of the 3rd command line argument in the raw_cmd pointer
	// which is inside the cmd1 struct, which is inside the struct that pipex points to"
	pipex->cmd1.args = NULL;
	// "Set the args pointer (which is inside cmd1 struct, inside the pipex struct) to NULL"
	pipex->cmd1.path = NULL;
	// "Set the path pointer (which is inside cmd1 struct, inside the pipex struct) to NULL"

	// Initialize second command
	pipex->cmd2.raw_cmd = argv[3];
	pipex->cmd2.args = NULL;
	pipex->cmd2.path = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (error_handler("Invalid arguments"));

	init_pipex(&pipex, argv, envp);

	if (safe_pipe(pipex.pipe) == -1)
		return (error_handler("Pipe failed"));

	pipex.pid = safe_fork();
	// program flow error handling
	if (pipex.pid == -1)
		return (error_handler("Fork failed"));

	if (pipex.pid == 0)
		handle_child(&pipex);
		// If successful, this process becomes cmd1 entirely
	else
	{
		if (safe_waitpid(pipex.pid, NULL, 0) == -1)
			return (error_handler("Waitpid failed"));
		// prototype: waitpid(childpid, &status, 0) : Suspends execution until child process terminates

		handle_parent(&pipex);
	}

	cleanup_pipex(&pipex);
	return (0);
}
