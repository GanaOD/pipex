/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/17 18:55:13 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Execute a parsed command using execve
** Command must be properly initialized with path and arguments (init_pipex)
*/
void execute_command(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->path || !cmd->args)
		exit_error("Invalid command structure");

	execve(cmd->path, cmd->args, envp);

	// This line only reached if execve failed:
	exit_error(cmd->path);
	printf("Debug: execve failed");
	// also specific error message: perror prints path as string, :, then the string describing the last error that occurred (from errno)
}
