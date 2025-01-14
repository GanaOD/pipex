/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:18:14 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/14 17:39:29 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

// Function prototypes
void    handle_child(char **argv, char **envp, int *pipe);
void    handle_parent(char **argv, char **envp, int *pipe);
void    execute_command(char *cmd, char **envp);
char    *find_command_path(char *cmd, char **envp);

#endif
