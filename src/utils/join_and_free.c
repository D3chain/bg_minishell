/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:08:38 by echatela          #+#    #+#             */
/*   Updated: 2025/09/15 12:08:46 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *dst, char *join, int i)
{
	char 	*tmp;

	tmp = dst;
	dst = ft_strjoin(dst, join);
	if (i == 1 || i == 3)
		free(tmp);
	if (i == 2 || i == 3)
		free(join);
	if (!dst)
		return (NULL);
	return (dst);
}