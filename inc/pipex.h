/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:14 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 15:58:44 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* 💫	INCLUDES	💫 */
/* Standard C library headers */
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
/* POSIX/System headers */
# include <fcntl.h>
# include <sys/wait.h>
# include <ctype.h>
/* Project headers */
# include "libft.h"

/* 💫	DATA STRUCTURES	💫 */
// for individual commands
typedef struct s_command
{
	char	*raw_cmd;
	char	**args;
	char	*path;
}	t_command;

// Main structure holding program state & resources
typedef struct s_pipex
{
	int			pipe[2];
	int			infile;
	int			outfile;
	t_command	cmd1;
	t_command	cmd2;
	char		**envp;
	char		**argv;
	pid_t		pid1;
	pid_t		pid2;
}	t_pipex;

/* 💫	CORE FUNCTION PROTOTYPES	💫 */

// 🌲	Core Pipeline Functions
// Command parsing and validation
int		parse_commands(t_pipex *pipex);
char	**split_with_quotes(const char *cmd);
// Process handling
void	handle_first_child(t_pipex *pipex);
void	handle_second_child(t_pipex *pipex);
// Command execution
int		execute_first_command(t_command *cmd, char **envp);
void	execute_second_command(t_command *cmd, char **envp);

// 🌲	Error Handling & System Calls
// Error management
void	exit_error(char *msg);
int		error_handler(char *msg);
// System call wrappers
int		safe_close(int fd);
pid_t	safe_fork(void);
int		safe_open(const char *path, int flags, mode_t mode);
int		safe_pipe(int pipefd[2]);
pid_t	safe_waitpid(pid_t pid, int *status, int options);

// 🌲	Resource Management
// Cleanup functions
void	ft_free_array(char **arr);
void	cleanup_command(t_command *cmd);
void	cleanup_pipex(t_pipex *pipex);

#endif
