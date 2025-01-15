/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:30:36 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Command execution module for pipex
** Handles the execution of parsed commands
*/

#include "pipex.h"

/*
** Execute a parsed command using execve
** Command must be properly initialized with path and arguments
*/
void execute_command(t_command *cmd, char **envp)
{
    if (!cmd || !cmd->path || !cmd->args)
        exit_error("Invalid command structure");

    execve(cmd->path, cmd->args, envp);
    // If we get here, execve failed
    exit_error("Execute failed");
}
