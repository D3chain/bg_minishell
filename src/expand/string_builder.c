/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:11:28 by echatela          #+#    #+#             */
/*   Updated: 2025/09/29 12:16:57 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_var(t_ms *ms, const char *p_arg, t_sb *cur, int *i)
{
	
}

int	sb_putc(t_sb *cur, char c)
{
	if (cur->i == cur->cap - 1)
	{
		cur->s = ms_realloc_array(cur->s, cur->cap, cur->cap * 2, sizeof(char));
		if (!cur->s)
			return (MS_ERR);
		cur->cap *= 2;
	}
	cur->s[cur->i++] = c;
	cur->s[cur->i] = 0;
	return (MS_OK);
}

int	sb_puts(t_sb *cur, const char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (sb_putc(cur, str[j]) != MS_OK)
			return (MS_ERR);
		j++;
	}
	return (MS_OK);
}

int	sb_detach_push(t_sb *cur, char **out_str, void *out, int argred)
{
	t_redir	red;

	if (cur->i == 0)
		return (free(cur->s), 0);
	*out_str = ft_strdup(cur->s);
	free(cur->s);
	if (!*out_str)
		return (MS_ERR);
	if (argred == 0)
		if (argvec_push_arg((t_argvec *)out, out_str) == MS_ERR)
			return (MS_ERR);
	if (argred == 1)
	{
		// gerer redir
		if (redirvec_push_redir((t_redirvec *)out, out_str) == MS_ERR)
			return (MS_ERR);
	}
	return (MS_OK);
}

int	sb_init(t_sb *sb)
{
	ft_bzero(sb, sizeof(*sb));
	sb->cap = SB_BUF_SIZE;
	sb->s = malloc(sizeof(char) * sb->cap);
	if (!sb->s)
		return (MS_ERR);
	return (MS_OK);
}
