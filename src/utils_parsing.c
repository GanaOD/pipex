/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:26:07 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/25 11:03:17 by go-donne         ###   ########.fr       */
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
	int		i;

	i = 0;
	len = ft_strlen(arg);
	if (!arg || len < 2)
		return (arg);
	new_arg = malloc(len - 1);
	if (!new_arg)
		return (NULL);
	while (arg[i + 1] != '\0')
	{
		new_arg[i] = arg[i + 1];
		i++;
	}
	new_arg[i] = '\0';
	free(arg);
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
