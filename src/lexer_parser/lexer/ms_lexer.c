/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:03:03 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:38:07 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_quote_err(t_lex *lex)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	ft_bzero(err_buf, MS_BUF_ERR_SIZE);
	i = 0;
	if (lex->in_sq)
		i += fill1(err_buf, "minishell: unexpexted EOF while looking for matching `''\n");
	if (lex->in_dq)
		i += fill1(err_buf + i, "minishell: unexpexted EOF while looking for matching `\"'\n");
	i += fill1(err_buf + i, "minishell: syntax error: unexpected end of file\n");
	write(2, err_buf, i);
	ft_bzero(&lex, sizeof(lex));
}

static t_tok	*ms_create_and_fill_vec(t_ms *ms, t_list **lst)
{
	t_tok	*vec;
	t_list	*cur;
	t_list	*tmp;
	int		i;

	vec = malloc(sizeof(t_tok) * ft_lstsize(lst));
	if (!vec)
		return (ms_fatal(ms, "malloc"), NULL);
	cur = (*lst);
	while (cur)
	{
		vec[i++] = (t_tok)cur->content;
		tmp = cur;
		cur = cur->next;
		free(cur);
	}
	return (vec);
}

static t_tok	*ms_lex_tokenize(t_ms *ms, t_lex *lex)
{
	t_list	*lst;
	t_list	*node;
	t_tok	*tok;

	lst = NULL;
	while (lex->src[lex->i])
	{
		if (is_blank(lex->src[lex->i]))
			lex->i++;
		else
		{
			node = ms_lex_read_get_node(ms, lex, &lst);
			if (!node)
				return (ms->status = MS_ERR, NULL);
			ft_lstadd_back(&lst, node);
		}
	}
	tok = ms_create_and_fill_vec(ms, &lst);
	return (tok);
}

t_tok	*ms_lexer(t_ms *ms, const char *line)
{
	t_lex	lex;

	ft_bzero(&lex, sizeof(lex));
	lex.src = line;
	lex.vec = ms_lex_tokenize(ms, &lex);
	if (lex.in_sq || lex.in_dq)
		return (ms_quote_err(&lex), ms->status = MS_MISUSE, NULL);
	return (lex.vec);
}

