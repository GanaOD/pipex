/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:21:44 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/22 14:42:21 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Initialize cmd struct with a raw cmd string
// Safer than direct assignment - validates input & sets pointers to NULL
// Returns 1 on success, 0 on failure

static int	init_command(t_command *cmd, char *raw_cmd)
{
	if (!raw_cmd)
		return (0);
	cmd->raw_cmd = raw_cmd;
	cmd->args = NULL;
	cmd->path = NULL;
	return (1);
}

// Check if command exists and is executable in given directory
// Returns heap-allocated full path if valid, NULL if not
static char	*try_path_access(char *dir, char *cmd)
{
	char	*path_join;
	char	*full_path;
	char	*valid_path;

	path_join = ft_strjoin(dir, "/");
	full_path = ft_strjoin(path_join, cmd);
	free(path_join);
	if (access(full_path, F_OK | X_OK) == 0)
	{
		valid_path = full_path;
		return (valid_path);
	}
	free (full_path);
	return (NULL);
}

// Search PATH environment variable for command executable
// Returns heap-allocated path if found, else copy of original command
static char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*valid_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_strdup(cmd));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		valid_path = try_path_access(paths[i], cmd);
		if (valid_path)
		{
			ft_free_array(paths);
			return (valid_path);
		}
		i++;
	}
	ft_free_array(paths);
	return (ft_strdup(cmd));
}

// Parse single command: split into args and find executable path
// Returns 1 on success (valid args & path found), 0 on any failure
static int	parse_command(t_command *cmd, char **envp)
{
	if (!cmd || !cmd->raw_cmd)
		return (0);
	cmd->args = split_with_quotes(cmd->raw_cmd);
	if (!cmd->args || !cmd->args[0])
		return (0);
	cmd->path = find_command_path(cmd->args[0], envp);
	if (!cmd->path)
	{
		ft_free_array(cmd->args);
		cmd->args = NULL;
		return (0);
	}
	return (1);
}

// Parse and validate both commands in pipeline
// Returns 1 if basic command structure valid (execution errors handled later)
int	parse_commands(t_pipex *pipex)
{
	if (!init_command(&pipex->cmd1, pipex->argv[2])
		|| !init_command(&pipex->cmd2, pipex->argv[3]))
		return (0);
	parse_command(&pipex->cmd1, pipex->envp);
	parse_command(&pipex->cmd2, pipex->envp);
	return (1);
}
