/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:10:40 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 11:29:54 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote_in_str(char *s)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			return (1);
		s++;
	}
	return (0);
}

static void	init_parsecmd(t_ms *ms, t_ast **node)
{
	*node = malloc(sizeof(t_ast));
	if (!*node)
		ms_fatal(ms, "parsecmd");
	ft_bzero(*node, sizeof(t_ast));
	(*node)->u_pao.cmd.hd_fd[0] = -1;	
	(*node)->u_pao.cmd.hd_fd[1] = -1;
	(*node)->u_pao.cmd.fd[0] = -1;
	(*node)->u_pao.cmd.fd[1] = -1;
	(*node)->kind = AST_CMD;	
	argvec_init(&(*node)->u_pao.cmd.argv);
	redirvec_init(&(*node)->u_pao.cmd.redv);
}

static void	parseredir(t_ms *ms, int *i, t_redirvec *redv)
{
	t_redir	red;

	if (ms->cyc.vec[*i].cat != TKC_REDIR)
		return ;
	red.kind = ms->cyc.vec[*i].kind - 2;
	*i += 1;
	if (ms->cyc.vec[*i].cat != TKC_WORD)
	{
		ms_syntax_err(ms->cyc.vec[*i].lex);
		ms->cyc.ret = MS_MISUSE;
		return ;
	}
	red.word = ms->cyc.vec[*i].lex;
	red.quoted_delim = 0;
	*i += 1;
	if (red.kind == AST_H_DOC && is_quote_in_str(red.word))
		expand_one(ms, &red.word, 1);
	if (red.kind == AST_H_DOC)
		ms->cyc.ret = AST_H_DOC;
	if (redirvec_push_redir(redv, &red) != MS_OK)
	{
		ms->cyc.ret = MS_ERR;
		return ;
	}
}

t_ast	*parsecmd(t_ms *ms, int *i)
{
	t_ast		*cmd;

	if (ms->cyc.vec[*i].kind == T_LPAR)
		return (*i += 1, parseblock(ms, i));
	if (ms->cyc.vec[*i].cat > TKC_REDIR)
		return (ms_syntax_err(ms->cyc.vec[*i].lex), ms->cyc.ret = MS_MISUSE, NULL);
	init_parsecmd(ms, &cmd);
	while (ms->cyc.vec[*i].cat <= TKC_REDIR)
	{
		if (ms->cyc.vec[*i].cat == TKC_WORD)
		{
			if (argvec_push_arg(&cmd->u_pao.cmd.argv, ms->cyc.vec[*i].lex) != MS_OK)
				return (ms->cyc.ret = MS_ERR, NULL);
			*i += 1;
		}
		parseredir(ms, i, &cmd->u_pao.cmd.redv);
		if (ms->cyc.ret == MS_ERR || ms->cyc.ret == MS_MISUSE)
			return (NULL);
		if (ms->cyc.ret == AST_H_DOC)
			set_h_doc_h_red(ms, &cmd->u_pao.cmd.redv.data[cmd->u_pao.cmd.redv.len - 1], cmd->u_pao.cmd.hd_fd);
	}
	return (cmd);
}
