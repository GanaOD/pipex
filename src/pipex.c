/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/16 12:17:16 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_parent(t_pipex *pipex)
{
	printf("Parent: Starting with pipe[0]=%d, pipe[1]=%d\n", pipex->pipe[0], pipex->pipe[1]);

	// Open output file
	pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("Parent: Opened outfile with fd=%d\n", pipex->outfile);
	if (pipex->outfile == -1)
		exit_error("Output file error");

	// Close stdin before duplicating
	if (safe_close(STDOUT_FILENO) == -1)
		exit_error("Failed to close stdout before duplication");

	// Redirect stdin to pipe read end
	printf("Parent: Redirecting stdin (0) to pipe[0]\n");
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to pipe read end");

	// Redirect stdout to outfile
	printf("Parent: Redirecting stdout (1) to outfile\n");
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to outfile");

	// Close unused file descriptors
	if (safe_close(pipex->pipe[0]) == -1)
		exit_error("Failed to close original pipe read end");
	if (safe_close(pipex->pipe[1]) == -1)
		exit_error("Failed to close pipe write end");
	if (safe_close(pipex->infile) == -1)
		exit_error("Failed to close original outfile");

	// Execute second command
	printf("Parent: About to execute wc\n");
	execute_command(&pipex->cmd2, pipex->envp);
}
void handle_child(t_pipex *pipex)
{
	// Open input file
	pipex->infile = safe_open(pipex->argv[1], O_RDONLY, 0644);
	printf("Child: Opened infile with fd=%d\n", pipex->infile);
	if (pipex->infile == -1)
		exit_error("Input file error");

	// Close stdin before duplicating (as dup2 requires inactive fildes before creating new reference to stdin)
	if (safe_close(STDIN_FILENO))
		exit_error("Failed to close stdin before duplication");

	// Redirect stdin to infile
	printf("Child: Redirecting stdin (0) to infile\n");
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		exit_error("Failed to redirect stdin to input file");

	// Redirect stdout to pipe write end
	printf("Child: Redirecting stdout (1) to pipe[1]\n");
	if(dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
		exit_error("Failed to redirect stdout to pipe write end");

	// Close unused file descriptors
	if (safe_close(pipex->pipe[0]) == -1)
		exit_error("Failed to close pipe read end");
	if (safe_close(pipex->pipe[1]) == -1)
		exit_error("Failed to close original pipe write end");
	if (safe_close(pipex->infile) == -1)
		exit_error("Failed to close original infile");

	// Execute first command
	printf("Child: About to execute grep\n");
	execute_command(&pipex->cmd1, pipex->envp);
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


	pipex->argv = argv;
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (error_handler("Invalid arguments"));

	printf("Main: Initializing pipex\n");
	init_pipex(&pipex, argv, envp);

	printf("Main: Creating pipe\n");
	if (safe_pipe(pipex.pipe) == -1)
		return (error_handler("Pipe failed"));

	printf("Main: Parsing commands\n");
	if (!parse_commands(&pipex))
		return (error_handler("Command parsing failed"));
	printf("Main: CMD1: %s, CMD2: %s\n", pipex.cmd1.path, pipex.cmd2.path);

	printf("Main: Forking process\n");
	pipex.pid = safe_fork();
	// program flow error handling
	if (pipex.pid == -1)
		return (error_handler("Fork failed"));

	if (pipex.pid == 0)
	{
		handle_child(&pipex);
		// If successful, this process becomes cmd1 entirely
		printf("Debug: Child process complete\n"); // This likely won't print if execve succeeds
	}
	else
	{
		printf("Debug: Parent process waiting for child\n");
		if (safe_waitpid(pipex.pid, NULL, 0) == -1)
			return (error_handler("Waitpid failed"));
		// prototype: waitpid(childpid, &status, 0) : Suspends execution until child process terminates
		printf("Debug: Child process finished, parent continuing\n");

		handle_parent(&pipex);
	}

	cleanup_pipex(&pipex);
	return (0);
}
