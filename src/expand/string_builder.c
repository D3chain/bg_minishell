/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:11:28 by echatela          #+#    #+#             */
/*   Updated: 2025/09/28 16:14:29 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sb_putc(t_sb *cur, char c)
{
	if (cur->i == cur->cap - 1)
	{
		cur->s = ms_realloc_array(cur->s, cur->cap, cur->cap * 2, )

	}
}

int	sb_detach(t_sb *cur, char **out)
{
	*out = ft_strdup(cur->s);
	free(cur->s);
	if (!*out)
		return (MS_ERR);
	return (MS_OK);
}

int	sb_init(t_sb *sb)
{
	ft_bzero(sb, sizeof(*sb));
	sb->cap = SB_BUF_SIZE;
	sb->s = malloc(sizeof(char) * sb->cap);
	if (!sb->s)
		return (MS_ERR);
	return (MS_OK)
}
