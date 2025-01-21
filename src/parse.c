/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:21:44 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/21 09:38:39 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Find full path of command by searching system's PATH variable
char	*find_command_path(char *cmd, char **envp)
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

/*
** Parse a command string into arguments
** Handles both normal & quotes args
** Returns 1 on success, 0 on failure
*/
int parse_command(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->raw_cmd)
		return (0);

	// Split raw command string into arguments, handling quotes
	cmd->args = split_with_quotes(cmd->raw_cmd);
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
** Parse both commands in pipex structure
** Returns 1 if both commands parsed successfully, 0 otherwise
*/
int	parse_commands(t_pipex *pipex)
{
	// Initialize both commands
    if (!init_command(&pipex->cmd1, pipex->argv[2]) ||
        !init_command(&pipex->cmd2, pipex->argv[3]))
        return (0);

    // Try to parse both commands but don't fail completely if one fails
    parse_command(&pipex->cmd1, pipex->envp);
    parse_command(&pipex->cmd2, pipex->envp);

    // Return success even if commands failed - failures handled in execution
    return (1);
}
