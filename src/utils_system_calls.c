/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system_calls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:14:23 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 11:53:38 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
System-level error reporting - wrapping around some system calls
	- dup(2) error-handling when called (handle_child & _parent)
	- No safe_execve needed, failure detected by reaching the next line
*/

int	safe_close(int fd)
{
	int	ret;
	ret = close(fd);
	if (ret == -1)
	{
		perror("close");
		return (-1);
	}
	return (0);
}

pid_t	safe_fork(void)
{
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	return (pid);
}

int	safe_open(const char *path, int flags, mode_t mode)
{
	int fd = open(path, flags, mode);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	safe_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1); // signal error to caller
	}
	return (0);
}

pid_t	safe_waitpid(pid_t pid, int *status, int options)
{
	pid_t result = waitpid(pid, status, options);
	if (result == -1 && errno != ECHILD) // only error if it's not "No child processes"
	{
		perror("waitpid");
		return (-1);
	}
	return (result);
}
