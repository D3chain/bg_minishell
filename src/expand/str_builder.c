/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:01:59 by echatela          #+#    #+#             */
/*   Updated: 2025/09/30 16:24:50 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_expand.h"

void	init_sb(t_sb *sb)
{
	sb->out = NULL;
	ft_bzero(sb->buf, (BUFFER_SIZE * sizeof(char)));
	sb->i = 0;
	sb->in_sq = 0;
	sb->in_dq = 0;
}

void	sb_add_reset_buf(t_ms *ms, t_sb *sb)
{
	char	*tmp;

	tmp = ft_strjoin(sb->out, sb->buf);
	if (!tmp)
		ms_fatal(ms, "expand");
	free(sb->out);
	sb->out = tmp;
	ft_bzero(sb->buf, (BUFFER_SIZE * sizeof(char)));
	sb->i = 0;
}

void	sb_puts(t_ms *ms, t_sb *sb, const char *s)
{
	while (*s)
	{
		sb_putc(ms, sb, *s);
		s++;
	}
}

void	sb_putc(t_ms *ms, t_sb *sb, char c)
{
	if (sb->i == BUFFER_SIZE - 2)
		sb_add_reset_buf(ms, sb);
	sb->buf[sb->i] = c;
	sb->i++;
}
