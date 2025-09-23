/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:10:40 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 21:15:51 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote_in_str(char *s)
{
	while (s)
	{
		if (*s == '\"' || *s == '\'')
			return (1);
		s++;
	}
	return (0);
}

static t_ret	ms_pars_cmd_redir(t_ms *ms, t_tok *vec, int *i, t_redirvec *redv)
{
	t_redir	red;
	
	red.kind = vec[*i++].kind - T_RED_IN;
	if (vec[*i].cat != TKC_WORD)
		return (ms_syntax_err(vec[*i].lex), MS_MISUSE);
	red.word = vec[*i++].lex;
	red.quoted_delim = 0;
	if (red.kind = AST_H_DOC && is_quote_in_str(red.word))
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
	(*node)->kind = AST_CMD;
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
			r = ms_pars_cmd_redir(ms, vec, i, &redv);
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
	return (ms_pars_add_node(ms, &node));
}
