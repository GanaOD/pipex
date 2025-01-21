/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:14 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/21 12:14:51 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


/* 💫	Includes ordered by type	💫 */

/* Standard C library headers */
# include <stdlib.h>     // malloc, free, exit
# include <unistd.h>     // fork, pipe, execve, etc
# include <errno.h>      // errno, error constants

/* POSIX/System headers */
# include <fcntl.h>      // open, constants
# include <sys/wait.h>   // wait, waitpid
# include <ctype.h>      // isspace, etc

/* Project headers */
# include "libft.h"		// my library functions



/* 💫	DATA STRUCTURES	💫 */

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
	pid_t		pid1;		// Process ID for fork 1
	pid_t		pid2;		// Process ID for fork 2
}	t_pipex;




/* 💫	CORE FUNCTION PROTOTYPES	💫 */

// Important / close to main program flow
// Core pipe handling, initialisation & setup (pipex.c)
void	init_pipex(t_pipex *pipex, char **argv, char **envp);


// Command/argument parsing & path resolution
// (parsing.c) Parsing logic flow:
int		parse_commands(t_pipex *pipex);
int		init_command(t_command *cmd, char *raw_cmd);
int		parse_command(t_command *cmd, char **envp);
char	*find_command_path(char *cmd, char **envp);

// (utils_parsing.c) Helper utils for specific parsing mechanics
// add const keyword back to char * param in split_with_quotes
char	**split_with_quotes(char *cmd);
int		is_quote(char c);
char	*remove_quotes(char *arg);


// Child process handling functions (child.c)
void 	handle_first_child(t_pipex *pipex);
void 	handle_second_child(t_pipex *pipex);


// Command execution logic (execute.c)
int		execute_first_command(t_command *cmd, char **envp);
void	execute_second_command(t_command *cmd, char **envp);


// Error handling (utils_error_handling.c)
void	exit_error(char *msg);
int		error_handler(char *msg);

// (utils_system_calls.c) Error-handling: system call wrappers
int 	safe_close(int fd);
pid_t	safe_fork(void);
int 	safe_open(const char *path, int flags, mode_t mode);
int		safe_pipe(int pipefd[2]);
pid_t	safe_waitpid(pid_t pid, int *status, int options);

// Cleanup (utils_cleanup.c)
void 	cleanup_pipex(t_pipex *pipex);
void	cleanup_command(t_command *cmd);
void	ft_free_array(char **arr);

#endif
