/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:03:03 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 12:53:02 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_quote_err(t_ms *ms)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	ft_bzero(err_buf, MS_BUF_ERR_SIZE);
	i = 0;
	if (ms->cyc.in_sq)
		i += fill1(err_buf, "minishell: unexpexted EOF while looking for matching `''\n");
	if (ms->cyc.in_dq)
		i += fill1(err_buf + i, "minishell: unexpexted EOF while looking for matching `\"'\n");
	i += fill1(err_buf + i, "minishell: syntax error: unexpected end of file\n");
	write(2, err_buf, i);
}

static t_ret	ms_lex_tokenize(t_ms *ms)
{
	t_tokvec	vec;
	t_tok		tok;
	int			i;

	tokv_init(&vec);
	i = 0;
	while (ms->cyc.line[i])
	{
		if (is_blank(ms->cyc.line[i]))
			i++;
		else
		{
			tok = ms_lex_read_get_tok(ms, &i);
			if (tokv_push_tok(&vec, &tok) != MS_OK)
				return (tokv_free(&vec), ms_cleanup_all(ms), MS_ERR);
			free(tok.lex);
		}
	}
	tokv_add_eof(&vec);
	ms->cyc.vec = vec.data;
	ms->cyc.tlen = vec.len;
	return (MS_OK);
}

t_ret	ms_lexer(t_ms *ms)
{
	t_ret	r;

	r = ms_lex_tokenize(ms);
	if (ms->cyc.in_sq || ms->cyc.in_dq)
		return (ms_quote_err(ms), MS_MISUSE);
	return (r);
}

