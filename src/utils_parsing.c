/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:26:07 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/18 13:06:47 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Remove quotes from an arg
char	*remove_quotes(char *arg)
{
	int		len;
	char	*new_arg;
	int		i;

	i = 0;
	len = ft_strlen(arg);
	new_arg = malloc(len - 1);

	// Skip quote at beginning
	while (arg[i + 1] != '\0')
	{
		new_arg[i] = arg[i + 1];
		i++:
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

	i = 0;
	args = ft_split(cmd, ' ');
	while (args[i])
	{
		if (is_quote(args[i][0]))
			// remove quotes from args
			args[i] = remove_quotes(args[i]);
		i++;
	}
	return (args);
}

// Check if char is a quote
static bool	is_quote(char c)
	return ((c == '"') || (c == '\''));
