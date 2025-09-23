/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 16:12:37 by echatela          #+#    #+#             */
/*   Updated: 2025/09/21 16:31:54 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

void	*ms_realloc_array(void *ptr, size_t old_n,
	size_t new_n, size_t elem_size)
{
	void	*q;
	size_t	ncopy;

	if (new_n == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (elem_size != 0 && new_n > SIZE_MAX / elem_size)
		return (NULL);
	q = malloc(new_n * elem_size);
	if (!q)
		return (NULL);
	if (ptr && old_n)
	{
		if (old_n < new_n)
			ncopy = old_n;
		else
			ncopy = new_n;
		ft_memcpy(q, ptr, ncopy * elem_size);
		free(ptr);
	}
	return (q);
}
