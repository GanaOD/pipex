/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/14 17:47:09 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void handle_parent(char **argv, char **envp, int *pipe)
{
    int outfile;

    // Open output file
    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
        exit(1);  // Will add error handling later

    // Redirect stdin to pipe and stdout to outfile
    dup2(pipe[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(pipe[1]);  // Close unused write end

    // Execute second command
    execute_command(argv[3], envp);
}

void handle_child(char **argv, char **envp, int *pipe)
{
	int	infile;

    // Open input file
    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
        exit(1);  // Will add error handling later

    // Redirect stdin to infile and stdout to pipe
    dup2(infile, STDIN_FILENO);
    dup2(pipe[1], STDOUT_FILENO);
    close(pipe[0]);  // Close unused read end

    // Execute first command
    execute_command(argv[2], envp);
}

int main(int argc, char **argv, char **envp)
{
    t_pipex  pipex;
    pid_t    pid;

    if (argc != 5)
        return (error_handler("Invalid arguments"));

    if (pipe(pipex.pipe) == -1)
        return (error_handler("Pipe failed"));

    pid = fork();
    if (pid == 0)
        handle_child(argv, envp, pipex.pipe);
    else
    {
        waitpid(pid, NULL, 0);
        handle_parent(argv, envp, pipex.pipe);
    }
    return (0);
}
