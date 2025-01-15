/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:14 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 17:59:02 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

// Structure for individual commands
typedef struct s_command
{
	char	*raw_cmd;	// Original command string
	char	**args;		// Split command arguments into array of strings
	char	*path;		// Full path to executable
}	t_command;

// Main structure holding program state
typedef struct s_pipex
{
	int			pipe[2];	// Pipe file descriptors
	int			infile;		// Input file descriptor
	int			outfile;	// Output file descriptor
	t_command	cmd1;		// First command
	t_command	cmd2;		// Second command
	char		**envp;		// Environment variables
	char		**argv;		// Program arguments
	pid_t		pid;		// Process ID for fork
}	t_pipex;


/* Error handling and cleanup functions (utils.c) - utility level */
void	ft_free_array(char **arr);
void	exit_error(char *msg);
void	cleanup_command(t_command *cmd);
int		error_handler(char *msg);


// Error-handling: system call wrappers (utils_system_calls.c)
int 	safe_close(int fd);
pid_t	safe_fork(void);
int 	safe_open(const char *path, int flags, mode_t mode);
int		safe_pipe(int pipefd[2]);
pid_t	safe_waitpid(pid_t pid, int *status, int options);


// Command execution logic (execute.c)
void execute_command(t_command *cmd, char **envp);


// Command/argument parsing & path resolution (parse.c)
int		init_command(t_command *cmd, char *raw_cmd);
int		parse_command(t_command *cmd, char **envp);
int		parse_commands(t_pipex *pipex);
char	*find_command_path(char *cmd, char **envp);


/* Main program flow (pipex.c) */
void 	cleanup_pipex(t_pipex *pipex);
void 	handle_child(t_pipex *pipex);
void 	handle_parent(t_pipex *pipex);
void    init_pipex(t_pipex *pipex, char **argv, char **envp);


#endif
