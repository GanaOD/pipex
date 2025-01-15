/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:00:26 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/*
** Execute a command by:
** 1. Split command string into program and arguments
** 2. Find program's full path
** 3. Execute program with arguments
** Example: "ls -l" -> program="ls", args=["ls", "-l", NULL]
*/
void execute_command(char *cmd, char **envp)
{
    char **args;    // Will hold ["ls", "-l", NULL]
    char *path;     // Will hold "/bin/ls"

    // Split "ls -l" into separate arguments
    args = ft_split(cmd, ' ');
    if (!args || !args[0])
        exit_error("Split failed");

    // Find full path to program
    path = find_command_path(args[0], envp);
    if (!path)
	{
		ft_free_array(args);
		exit_error("Command not found");
	}

    // Execute program (if successful, this replaces current process)
    execve(path, args, envp);

    // If we get here, execve failed
	free(path);
	ft_free_path(args);
    exit_error("Execute failed")
}
