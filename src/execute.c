/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/26 09:45:46 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Handles specific error types returned by execve system call
// Prints error message to stdout or stderr as appropriate for each case
// Returns error code matching shell behavior, or -1 if error not recognized
// Note: Messages sent to stdout to stay in pipeline data flow
// Error codes: 127 (cmd not found), 126 (cmd not executable), 1 (general error)
static int	get_specific_error_code(char *cmd_name)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("Command not found: ", STDOUT_FILENO);
		if (cmd_name)
			ft_putstr_fd(cmd_name, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (127);
	}
	else if (errno == EACCES)
	{
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		return (126);
	}
	else if (errno == EISDIR)
	{
		ft_putendl_fd("Is a directory", STDERR_FILENO);
		exit(126);
	}
	else if (errno == ENOMEM)
	{
		ft_putendl_fd("Cannot allocate memory", STDERR_FILENO);
		return (1);
	}
	return (-1);
}

// Main error handler for command execution failures
// Extracts command name if available and delegates to specific error handler
// Falls back to standard perror if error not specifically handled
// Returns appropriate shell-compatible exit code
static int	handle_execution_error(t_command *cmd)
{
	char	*cmd_name;
	int		error_code;

	cmd_name = NULL;
	if (cmd && cmd->args && cmd->args[0])
		cmd_name = cmd->args[0];
	error_code = get_specific_error_code(cmd_name);
	if (error_code != -1)
		return (error_code);
	perror("");
	return (1);
}

// Execute cmd1, return on failure
int	execute_first_command(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->path || !cmd->args)
		return (127);
	execve(cmd->path, cmd->args, envp);
	return (handle_execution_error(cmd));
}

// Execute cmd2. Never returns: either succeeds (execve) or exits
void	execute_second_command(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->path || !cmd->args)
	{
		ft_putendl_fd("pipex: invalid command structure", STDERR_FILENO);
		exit(1);
	}
	execve(cmd->path, cmd->args, envp);
	exit (handle_execution_error(cmd));
}
