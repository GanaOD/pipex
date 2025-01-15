/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:04:43 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/15 12:39:30 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Command parsing module for pipex - Basic Structure
*/

#include "pipex.h"

static char	*find_command_path(const char *cmd, char **envp);

/*
** Initialize a command structure with basic values
*/
int	init_command(t_command *cmd, const char *raw_cmd)
{
    cmd->raw_cmd = raw_cmd;  // Points to argv
    cmd->args = NULL;
    cmd->path = NULL;
    return (1);
}

/*
** Parse a command into arguments and find its path
*/
int	parse_command(t_command *cmd, char **envp)
{
    // Split command string into argument array
    cmd->args = ft_split(cmd->raw_cmd, ' ');

    // Find full executable path
    cmd->path = find_command_path(cmd->args[0], envp);

    return (1);
}

/*
** Parse both commands in the pipeline
*/
int	parse_pipeline(t_pipex *pipex)
{
    // Initialize both command structures
    init_command(&pipex->cmd1, pipex->argv[2]);
    init_command(&pipex->cmd2, pipex->argv[3]);

    // Parse both commands
    parse_command(&pipex->cmd1, pipex->envp);
    parse_command(&pipex->cmd2, pipex->envp);

    return (1);
}

/*
** Clean up a command structure - free allocated memory
*/
void	cleanup_command(t_command *cmd)
{
    if (cmd->args)
        ft_free_array(cmd->args);
    if (cmd->path)
        free(cmd->path);
    cmd->args = NULL;
    cmd->path = NULL;
    cmd->raw_cmd = NULL;  // Don't free - points to argv
}

/*
** Find command path by searching through PATH directories
*/
static char	*find_command_path(const char *cmd, char **envp)
{
    char	**paths;
    char	*path_join;
    char	*full_path;
    int		i;

    // Find PATH in environment
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
        i++;

    // Split PATH into directories
    paths = ft_split(envp[i] + 5, ':');

    // Try each directory until we find executable
    i = 0;
    while (paths[i])
    {
        path_join = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(path_join, cmd);
        free(path_join);

        if (access(full_path, F_OK | X_OK) == 0)
        {
            ft_free_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_array(paths);
    return (NULL);
}
