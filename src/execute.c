/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/19 16:57:19 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Execute a parsed command using execve
** Command must be properly initialized with path and arguments (init_pipex)
*/
void execute_command(t_command *cmd, char **envp)
{
	// Check valid command structure
	if (!cmd || !cmd->path || !cmd->args)
		exit_error("Invalid command structure");

	execve(cmd->path, cmd->args, envp);

	// If execve failed, format error prefix
    ft_putstr_fd("pipex: ", STDERR_FILENO);
    ft_putstr_fd(cmd->args[0], STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);

    // Handle specific error cases
    if (errno == ENOENT)
    {
        ft_putendl_fd("command not found", STDERR_FILENO);
        exit(127);
    }
    else if (errno == EACCES)
    {
        ft_putendl_fd("Permission denied", STDERR_FILENO);
        exit(126);
    }
    else if (errno == EISDIR)
    {
        ft_putendl_fd("Is a directory", STDERR_FILENO);
        exit(126);
    }
    else if (errno == ENOMEM)
    {
        ft_putendl_fd("Cannot allocate memory", STDERR_FILENO);
        exit(1);
    }
    else
    {
        // For any other errors, use perror's standard messages
        perror("");
        exit(1);
    }
}
