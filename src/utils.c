/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:05:16 by go-donne          #+#    #+#             */
/*   Updated: 2025/01/14 17:47:31 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
utils.c:
- path finding functions
- string/command parsing functions
- error handling functions
*/

void exit_error(char *msg)
{
    perror(msg);
    exit(1);
}
