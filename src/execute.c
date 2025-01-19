/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/19 13:56:32 by go-donne         ###   ########.fr       */
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



	// DEBUGGING: print full command structure
	ft_putstr_fd("\n=== Command Execution Debug ===\n", 2);
    ft_putstr_fd("Path: ", 2);
    ft_putstr_fd(cmd->path, 2);
    ft_putstr_fd("\nArguments:\n", 2);

	int i = 0;
    while (cmd->args[i])
    {
        ft_putstr_fd("[", 2);
        ft_putstr_fd(cmd->args[i], 2);
        ft_putstr_fd("]\n", 2);
        i++;
    }
    ft_putstr_fd("========================\n", 2);



	execve(cmd->path, cmd->args, envp);


	// DEBUGGING
	ft_putstr_fd("execve failed for command: ", 2);
    ft_putstr_fd(cmd->path, 2);
    ft_putstr_fd("\n", 2);
    perror("execve");
    exit(EXIT_FAILURE);


	// // This line only reached if execve failed:
	// exit_error(cmd->path);
	// printf("Debug: execve failed");
	// // also specific error message: perror prints path as string, :, then the string describing the last error that occurred (from errno)
}
