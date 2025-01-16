/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_system_calls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:14:23 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/16 11:25:41 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
System-level error reporting: wrapping around system calls: forking, opening file, pipe creation
	- dup(2) error-handling when called (handle_child & _parent)
	- No safe_execve needed:
		- execve's error handling is unique - we detect failure by reaching the next line
		- The function is only used in one place
		- We can't meaningfully return an error status since execve replaces the process on success
*/

int safe_close(int fd)
{
	int	ret;
	ret = close(fd);
	if (ret == -1)
	{
		perror("close");
		return (-1);
	}
	printf("Debug: safely closed\n");
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
	printf("Debug: safe fork success\n");
	return (pid);
}

int	safe_open(const char *path, int flags, mode_t mode)
{
	int fd = open(path, flags, mode);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	printf("Debug: safely opened\n");
	return (fd);
}

int	safe_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1); // signal error to caller
	}
	printf("Debug: safe pipe success\n");
	return (0);
}

pid_t	safe_waitpid(pid_t pid, int *status, int options)
{
	pid_t result = waitpid(pid, status, options);
	if (result == -1)
	{
		perror("waitpid");
		return (-1);
	}
	printf("Debug: safe waitpid\n");
	return (result);
}
