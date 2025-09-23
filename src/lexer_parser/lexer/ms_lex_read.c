/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lex_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:49:42 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 12:53:45 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_wordlen(t_ms *ms, int *i)
{
	size_t	len;

	len = 0;
	while (ms->cyc.line[*i + len])
	{
		if (!ms->cyc.in_sq && !ms->cyc.in_dq && (is_blank(ms->cyc.line[*i + len])
			|| is_meta(ms->cyc.line[*i + len])))
			break;
		else if (!ms->cyc.in_dq && ms->cyc.line[*i + len] == '\'')
			ms->cyc.in_sq = !ms->cyc.in_sq;
		else if (!ms->cyc.in_sq && ms->cyc.line[*i + len] == '\"')
			ms->cyc.in_dq = !ms->cyc.in_dq;
		len++;
	}
	return (len);
}

static t_tok	ms_lex_read_word(t_ms *ms, int *i)
{
	char	*str;
	int		wd_len;

	wd_len = ms_wordlen(ms, i);
	str = ft_substr(ms->cyc.line, *i, wd_len);
	if (!str)
		ms_fatal(ms, "malloc");
	return (*i += wd_len, ms_create_tok(T_WORD, str));
}

static t_tok	ms_lex_read_op(t_ms *ms, int *i)
{
	const char	*op[] = {0, "|", "||", "&&", "(", ")", "<", "<<", ">", ">>"};
	char		*str;
	int			ind;

	ind = sizeof(op) / sizeof(*op);
	while (op[--ind])
	{
		if (ft_strncmp(&ms->cyc.line[*i], op[ind], ft_strlen(op[ind])) == 0)
		{
			str = ft_substr(ms->cyc.line, *i, ft_strlen(op[ind]));
			if (!str)
				ms_fatal(ms, "malloc");
			return (*i += ft_strlen(op[ind]), ms_create_tok(ind, str));
		}
	}
	str = ft_substr(ms->cyc.line, *i, 1);
	return (*i += 1, ms_create_tok(T_UNSUP, str));
}

t_tok	ms_lex_read_get_tok(t_ms *ms, int *i)
{
	if (is_meta(ms->cyc.line[*i]))
		return (ms_lex_read_op(ms, i));
	else
		return (ms_lex_read_word(ms, i));
}
