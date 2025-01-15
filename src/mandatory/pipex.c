/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:08:35 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_child(t_pipex *pipex)
{
    // Open input file
    pipex->infile = open(pipex->argv[1], O_RDONLY);
    if (pipex->infile == -1)
        exit_error("Input file error");

    // Redirect stdin to infile and stdout to pipe
    dup2(pipex->infile, STDIN_FILENO);
    dup2(pipex->pipe[1], STDOUT_FILENO);
    close(pipex->pipe[0]);  // Close unused read end

    // Execute first command
    execute_command(&pipex->cmd1, pipex->envp);
}

void handle_parent(t_pipex *pipex)
{
    // Open output file
    pipex->outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->outfile == -1)
        exit_error("Output file error");

    // Redirect stdin to pipe and stdout to outfile
    dup2(pipex->pipe[0], STDIN_FILENO);
    dup2(pipex->outfile, STDOUT_FILENO);
    close(pipex->pipe[1]);  // Close unused write end

    // Execute second command
    execute_command(&pipex->cmd2, pipex->envp);
}

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
    pipex->cmd1.args = NULL;
    pipex->cmd1.path = NULL;

    // Initialize second command
    pipex->cmd2.raw_cmd = argv[3];
    pipex->cmd2.args = NULL;
    pipex->cmd2.path = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_pipex  pipex;

    if (argc != 5)
        return (error_handler("Invalid arguments"));

    init_pipex(&pipex, argv, envp);

    if (pipe(pipex.pipe) == -1)
        return (error_handler("Pipe failed"));

	pipex.pid = fork();
	if (pipex.pid == -1)
		return (error_handler("Fork failed"));

    if (pipex.pid == 0)
        handle_child(&pipex);
    else
    {
        waitpid(pipex.pid, NULL, 0);
        handle_parent(&pipex);
    }

    cleanup_pipex(&pipex);
    return (0);
}
