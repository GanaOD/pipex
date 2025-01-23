/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: go-donne <go-donne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:45:58 by go-donne          #+#    #+#             */
/*   Updated: 2024/11/05 10:11:22 by go-donne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated_mem;
	size_t	total_size;

	total_size = count * size;
	if (count != 0 && (total_size / count != size))
		return (NULL);
	allocated_mem = malloc(total_size);
	if (allocated_mem != NULL)
		ft_memset(allocated_mem, 0, total_size);
	return (allocated_mem);
}
