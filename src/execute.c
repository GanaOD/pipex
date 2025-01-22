/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 11:16:30 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Handle errors from execve with appropriate error messages and exit codes
** Returns appropriate exit code based on error type
*/

static int	handle_execution_error(t_command *cmd)
{
	char	*cmd_name;
	cmd_name = NULL;

	// Extract cmd name if available
    if (cmd && cmd->args && cmd->args[0])
		cmd_name = cmd->args[0];

	// // Error prefix formatting (all to stdout for pipe) & make sure ends with \n
	// ft_putstr_fd("pipex: ", STDOUT_FILENO);
	// if (cmd_name)
    //     ft_putstr_fd(cmd_name, STDOUT_FILENO);
    // ft_putstr_fd("\n", STDOUT_FILENO);

    // Handle specific error cases. All to stdout to match bash
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
    else
    {
        // For any other errors, use perror's standard messages
        perror("");
        return (1);
    }
}


/*
** Execute first command - continue on failure
** Returns exit code for parent process to handle
*/

int	execute_first_command(t_command *cmd, char **envp)
{
	// If command structure is invalid, return error code 127 but don't exit
	if (!cmd || !cmd->path || !cmd->args)
		return (127);

	execve(cmd->path, cmd->args, envp);

	return (handle_execution_error(cmd));
}


/*
** Execute second command - exit on failure
** Never returns as it either succeeds (execve) or exits
*/

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
