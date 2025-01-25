/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:26:07 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/25 18:05:27 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Check if char is a quote
static int	is_quote(char c)
{
	return ((c == '"') || (c == '\''));
}

// Remove quotes from an arg
static char	*remove_quotes(char *arg)
{
	int		len;
	char	*new_arg;

	len = ft_strlen(arg);
	if (!arg || len < 2)
		return (arg);
	if (!is_quote(arg[0] || arg[0] != arg[len - 1]))
		return (arg);
	new_arg = malloc(len - 1);
	if (!new_arg)
		return (NULL);
	ft_strlcpy(new_arg, arg + 1, len - 1);
	free (arg);
	return (new_arg);
}

// Split cmd string & handle quotes
char	**split_with_quotes(const char *cmd)
{
	char	**args;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (is_quote(args[i][0]))
		{
			args[i] = remove_quotes(args[i]);
			if (!args[i])
			{
				while (i > 0)
					free (args[--i]);
				free (args);
				return (NULL);
			}
		}
		i++;
	}
	return (args);
}

// Get PATH string from environment variables
// Returns pointer to PATH string (after "PATH=") or empty string if not found
static char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return ("");
	return (envp[i] + 5);
}

// Search PATH for executable
// Returns heap-allocated path if found, copy of cmd if not found
char	*search_path_dirs(char *cmd, char **envp)
{
	char	**paths;
	char	*valid_path;
	char	*path_str;
	int		i;

	path_str = get_path_from_env(envp);
	paths = ft_split(path_str, ':');
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
