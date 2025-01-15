/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:21:44 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:28:26 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Command parsing module for pipex
** Handles command string parsing and command structure initialization
*/

#include "pipex.h"

/*
** Initialize a command structure with a raw command string
** Returns 1 on success, 0 on failure
*/
int init_command(t_command *cmd, char *raw_cmd)
{
    if (!raw_cmd)
        return (0);
    cmd->raw_cmd = raw_cmd;
    cmd->args = NULL;
    cmd->path = NULL;
    return (1);
}

/*
** Parse a command string into arguments
** Handles both space separation and quotes
** Returns 1 on success, 0 on failure
*/
int parse_command(t_command *cmd, char **envp)
{
    if (!cmd || !cmd->raw_cmd)
        return (0);

    // Split command into arguments
    cmd->args = ft_split(cmd->raw_cmd, ' ');
    if (!cmd->args || !cmd->args[0])
        return (0);

    // Find command path
    cmd->path = find_command_path(cmd->args[0], envp);
    if (!cmd->path)
    {
        ft_free_array(cmd->args);
        cmd->args = NULL;
        return (0);
    }

    return (1);
}

/*
** Clean up command structure
** Frees all allocated memory
*/
void cleanup_command(t_command *cmd)
{
    if (cmd->args)
        ft_free_array(cmd->args);
    if (cmd->path)
        free(cmd->path);
    cmd->args = NULL;
    cmd->path = NULL;
    cmd->raw_cmd = NULL;  // Don't free as it points to argv
}

/*
** Parse both commands in pipex structure
** Returns 1 if both commands parsed successfully, 0 otherwise
*/
int parse_commands(t_pipex *pipex)
{
    if (!init_command(&pipex->cmd1, pipex->argv[2]) ||
        !init_command(&pipex->cmd2, pipex->argv[3]))
        return (0);

    if (!parse_command(&pipex->cmd1, pipex->envp))
    {
        cleanup_command(&pipex->cmd1);
        return (0);
    }

    if (!parse_command(&pipex->cmd2, pipex->envp))
    {
        cleanup_command(&pipex->cmd1);
        cleanup_command(&pipex->cmd2);
        return (0);
    }

    return (1);
}

/*
** Find executable path from command name by:
** 1. Get PATH variable from environment
** 2. Split PATH into directories
** 3. Try each directory to find command
** Example: "ls" -> "/bin/ls"
*/
char *find_command_path(char *cmd, char **envp)
{
    char	**paths;
	char	*path_join;
    char	*full_path;
    int i;

    // Find PATH in environment variables
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    // If no PATH found, command won't be found
    if (!envp[i])
        return (NULL);

    // Split PATH into individual directories (e.g., "/bin:/usr/bin" -> ["/bin", "/usr/bin"])
    paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);

    // Try each directory
    i = 0;
    while (paths[i])
    {
        // Build full path (e.g., "/bin" + "/" + "ls" -> "/bin/ls")
        path_join = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(path_join, cmd);
		free(path_join);

        // Check if file exists and is executable
        if (access(full_path, F_OK | X_OK) == 0)
        {
			// Free paths array but keep successful full_path
			ft_free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
    }
	ft_free_array(paths);
	return (NULL);
}
