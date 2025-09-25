/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:10:40 by echatela          #+#    #+#             */
/*   Updated: 2025/09/25 10:25:17 by echatela         ###   ########.fr       */
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

static void	init_parsecmd(t_ms *ms, t_ast **node, t_redirvec *redv, t_argvec *argv)
{
	*node = malloc(sizeof(t_ast));
	if (!*node)
		ms_fatal(ms, "parsecmd");
	ft_bzero(*node, sizeof(t_ast));
	(*node)->kind = AST_CMD;	
	redirvec_init(redv);
	argvec_init(argv);
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
		red.quoted_delim = 1;
	if (redirvec_push_redir(redv, &red) != MS_OK)
	{
		ms->cyc.ret = MS_ERR;
		return ;
	}
}

static void	fillcmd(t_ast **cmd, t_redirvec redv, t_argvec argv)
{
	t_cmd	v_cmd;
	
	v_cmd.argv = argv.data;
	v_cmd.argc = argv.len;
	v_cmd.redirs = redv.data;
	v_cmd.redir_count = redv.len;
	(*cmd)->u_pao.cmd = v_cmd;
}

t_ast	*parsecmd(t_ms *ms, int *i)
{
	t_ast		*cmd;
	t_redirvec	redv;
	t_argvec	argv;

	if (ms->cyc.vec[*i].kind == T_LPAR)
		return (*i += 1, parseblock(ms, i));
	if (ms->cyc.vec[*i].cat > TKC_REDIR)
		return (ms_syntax_err(ms->cyc.vec[*i].lex), ms->cyc.ret = MS_MISUSE, NULL);
	init_parsecmd(ms, &cmd, &redv, &argv);
	while (ms->cyc.vec[*i].cat <= TKC_REDIR)
	{
		if (ms->cyc.vec[*i].cat == TKC_WORD)
		{
			if (argvec_push_arg(&argv, ms->cyc.vec[*i].lex) != MS_OK)
				return (ms->cyc.ret = MS_ERR, NULL);
			*i += 1;
		}
		parseredir(ms, i, &redv);
		if (ms->cyc.ret != MS_OK)
			return (NULL);
	}
	fillcmd(&cmd, redv, argv);
	return (cmd);
}
