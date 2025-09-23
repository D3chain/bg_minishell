/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:36:54 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 20:28:17 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_pars_redir(t_ms *ms, t_tok *vec, int *i, t_redirvec *redv)
{
	t_redir	red;
	
	red.kind = vec[*i++].kind - T_RED_IN;
	if (vec[*i].cat != TKC_WORD)
		return (ms_syntax_err(vec[*i].lex), MS_MISUSE);
	red.word = vec[*i++].lex;
	red.quoted_delim = 0;
	if (red.kind = AST_H_DOC && is_quote_in(red.word))
		red.quoted_delim = 1;
	if (redirvec_push_redir(redv, &red) != MS_OK)
		return (MS_ERR);
	return (MS_OK);
}

static void	init_pars_cmd(t_ast **node, t_redirvec *redv, t_argvec *argv, t_ret *r)
{
	*r = MS_OK;
	*node = malloc(sizeof(t_ast));
	if (!*node)
	{
		*r = MS_ERR;
		return ;
	}
	ft_bzero(*node, sizeof(t_ast));
	redirvec_init(redv);
	argvec_init(argv);
	
}

t_ret	ms_pars_cmd(t_ms *ms, t_tok *vec, int *i)
{
	t_ast	*node;
	t_redirvec	redv;
	t_argvec	argv;
	t_ret		r;

	init_pars_cmd(&node, &redv, &argv, &r);
	if (r == MS_ERR)
		return (MS_ERR);
	while (vec[*i].cat == TKC_REDIR || vec[*i].cat == TKC_WORD)
	{
		if (vec[*i].cat == TKC_REDIR)
		{
			r = ms_pars_redir(ms, vec, i, &redv);
			if (r != MS_OK)
				return (r);
			node->u_pao.cmd.redir_count++;
		}
		else
		{
			if (argvec_push_arg(&argv, vec[*i++].lex) != MS_OK)
				return (MS_ERR);
			node->u_pao.cmd.argc++;
		}
	}
	return (MS_OK);
}

t_ret	ms_parser(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->cyc.vec[i - 1].cat != TKC_EOF)
	{
		if (ms->cyc.vec[i].cat == TKC_REDIR || ms->cyc.vec[i].cat == TKC_WORD)
			return (ms_syntax_err(ms->cyc.vec[i].lex), MS_MISUSE);
		ms_pars_cmd(ms, ms->cyc.vec, &i);
	}
	return(MS_OK);
}
