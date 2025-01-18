/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/18 11:25:11 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Initialise pipex structure with starting values & command configurations
@param pipex:	pointer to pipex structure
@param argv:	array of command-line arguments passed at execution
@param envp:	array of environment variables from shell environment
*/
void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	// Initialize file descriptors to -1 (invalid/unused state)
	// to help error checking & cleanup later
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;

	// Store pointer to environment variables array
	pipex->envp = envp;

	// Store pointer to command-line arguments array
	pipex->argv = argv;

	// Initialize first command struct (cmd1), from argv[2]
	pipex->cmd1.raw_cmd = argv[2];	// store raw command string
	pipex->cmd1.args = NULL;		// will hold command args after split
	pipex->cmd1.path = NULL;		// will hold full path to executable

	// Initialize second command struct (cmd2), contained in argv[3]
	pipex->cmd2.raw_cmd = argv[3];
	pipex->cmd2.args = NULL;
	pipex->cmd2.path = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	// Validate nr. of arguments
	if (argc != 5)
		return (error_handler("Invalid arguments"));

	// Check for null pointers from shell
	if (!argv || !envp)
		return (error_handler("Invalid shell environment"));

	// Params valid, now initialise pipex
	init_pipex(&pipex, argv, envp);

	if (!parse_commands(&pipex))
		return (error_handler("Command parsing failed"));

	// Create pipe
	if (safe_pipe(pipex.pipe) == -1)
		return (error_handler("Pipe failed"));

	// 1st fork
	pipex.pid1 = safe_fork();
	if (pipex.pid1 ==-1)
		return (error_handler("First fork failed"));
	if (pipex.pid1 == 0)	// 1st child
		handle_first_child(&pipex);

	// 2nd fork
	pipex.pid2 = safe_fork();
	if (pipex.pid2 == -1)
		return (error_handler("Second fork failed"));
	if (pipex.pid2 == 0)	// 2nd child
		handle_second_child(&pipex);

	// Parent process
	// Close pipe ends in parent: not needed
	safe_close(pipex.pipe[0]);
	safe_close(pipex.pipe[1]);

	// Wait for both children to finish
	safe_waitpid(pipex.pid1, NULL, 0);
	safe_waitpid(pipex.pid2, NULL, 0);

	cleanup_pipex(&pipex);
	return (0);
}
