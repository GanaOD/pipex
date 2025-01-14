/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:40:24 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/14 17:47:17 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *find_command_path(char *cmd, char **envp)
{
    char **paths;   // Array of possible paths from PATH variable
    char *full_path;
    int i = 0;

    // Get PATH from environment variables
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;
    if (!envp[i])
        return (NULL);

    paths = ft_split(envp[i] + 5, ':');  // Split PATH into individual directories
    // Try each path + command until we find one that exists...
    // Return full path to command
    return (full_path);
}

void execute_command(char *cmd, char **envp)
{
    char **args;    // Will hold command + arguments
    char *path;     // Will hold full path to executable

    args = ft_split(cmd, ' ');  // Split "ls -l" into {"ls", "-l", NULL}
    path = find_command_path(args[0], envp);  // Find /bin/ls
    execve(path, args, envp);
    // If execve returns, there was an error
    exit(1);
}
