/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 12:24:27 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_input(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (error_handler("Invalid arguments"));
	if (!argv || !envp)
		return (error_handler("Invalid shell environment"));
	return (1);
}

/*
Initialise pipex structure with starting values & command configurations
@param pipex:	pointer to pipex structure
@param argv:	array of command-line arguments passed at execution
@param envp:	array of environment variables from shell environment
Initialising fds to -1 (invalid/unused state): helps error checking & clean up
Initialising cmd1 struct from argv[2] & cmd2 struct from argv[3]
*/
static void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pipe[0] = -1;
	pipex->pipe[1] = -1;
	pipex->envp = envp;
	pipex->argv = argv;
	pipex->cmd1.raw_cmd = argv[2];
	pipex->cmd1.args = NULL;
	pipex->cmd1.path = NULL;
	pipex->cmd2.raw_cmd = argv[3];
	pipex->cmd2.args = NULL;
	pipex->cmd2.path = NULL;
}

static int	create_pipeline(t_pipex *pipex)
{
	if (safe_pipe(pipex->pipe) == -1)
		return (error_handler("Pipe failed"));
	pipex->pid1 = safe_fork();
	if (pipex->pid1 == -1)
		return (error_handler("First fork failed"));
	if (pipex->pid1 == 0)
		handle_first_child(pipex);
	pipex->pid2 = safe_fork();
	if (pipex->pid2 == -1)
		return (error_handler("Second fork failed"));
	if (pipex->pid2 == 0)
		handle_second_child(pipex);
	return (1);
}

static int	cleanup_and_exit(t_pipex *pipex)
{
	int		status;

	safe_close(pipex->pipe[0]);
	safe_close(pipex->pipe[1]);
	if (safe_waitpid(pipex->pid2, &status, 0) == -1)
		return (error_handler("Second wait failed"));
	cleanup_pipex(pipex);
	return (WEXITSTATUS(status));
}

// Handles main program flow: process creation, management
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (!validate_input(argc, argv, envp))
		return (error_handler("Invalid arguments"));
	init_pipex(&pipex, argv, envp);
	if (!parse_commands(&pipex))
		return (error_handler("Command parsing failed"));
	if (!create_pipeline(&pipex))
		return (error_handler("Pipeline creation failed"));
	return (cleanup_and_exit(&pipex));
}
