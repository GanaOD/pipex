/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:14 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:05:14 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_command
{
    char    *raw_cmd;    // Original command string
    char    **args;      // Split command arguments
    char    *path;       // Full path to executable
}   t_command;

typedef struct s_pipex
{
    int         pipe[2];     // Pipe file descriptors
    int         infile;      // Input file descriptor
    int         outfile;     // Output file descriptor
    t_command   cmd1;        // First command
    t_command   cmd2;        // Second command
    char        **envp;      // Environment variables
    pid_t       pid;         // Process ID for fork
}   t_pipex;


// pipex.c
void    handle_child(char **argv, char **envp, int *pipe);
void    handle_parent(char **argv, char **envp, int *pipe);

// execute.c
void	execute_command(char *cmd, char **envp);
char	*find_command_path(char *cmd, char **envp);

// utils.c
void exit_error(char *msg)

#endif
