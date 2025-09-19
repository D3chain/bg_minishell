/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lex_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:49:42 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:40:06 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_wordlen(t_lex *lex)
{
	size_t	len;

	len = 0;
	while (lex->src[lex->i + len])
	{
		if (!lex->in_sq && !lex->in_dq && (is_blank(lex->src[lex->i + len]) ||
			is_meta(lex->src[lex->i + len])))
			break;
		else if (!lex->in_dq && lex->src[lex->i + len] == '\'')
			lex->in_sq = !lex->in_sq;
		else if (!lex->in_sq && lex->src[lex->i + len] == '\"')
			lex->in_dq = !lex->in_dq;
		len++;
	}
	return (len);
}

static t_tok	ms_lex_read_word(t_lex *lex)
{
	char	*str;
	int		wd_len;

	wd_len = ms_wordlen(lex);
	str = ft_substr(lex->src, lex->i, wd_len);
	if (!str)
		return (NULL);
	return (lex->i += wd_len, ms_create_tok(T_WORD, str));
}

static t_tok	ms_lex_read_op(t_lex *lex)
{
	const char	*op[] = {0, "|", "||", "&&", "(", ")", "<", "<<", ">", ">>"};
	char		*str;
	int			i;

	i = sizeof(op) / sizeof(*op);
	while (op[--i])
	{
		if (ft_strncmp(&lex->src[lex->i], op[i], ft_strlen(op[i])) == 0)
		{
			str = ft_substr(lex->src, lex->i, ft_strlen(op[i]));
			if (!str)
				return (NULL);
			return (lex->i += ft_strlen(op[i]), ms_create_tok(i, str));
		}
	}
	str = ft_substr(lex->src, lex->i, 1);
	return (lex->i += 1, ms_create_tok(T_UNSUP, str));
}

t_list	*ms_lex_read_get_node(t_ms *ms, t_lex *lex, t_list **lst)
{
	t_list	*node;
	t_tok	tok;

	if (is_meta(lex->src[lex->i]))
		tok = ms_lex_read_op(lex);
	else
		tok = ms_lex_read_word(lex);
	if (!tok)
		return (ft_lstclear(lst, ms_tok_del), ms->status = MS_ERR, NULL);
	node = ft_lstnew(tok);
	if (!node)
		return (ms_tok_del(tok), ft_lstclear(lst, ms_tok_del), ms->status = MS_ERR, NULL);
	return (node);
}
