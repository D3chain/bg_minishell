/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:05:01 by echatela          #+#    #+#             */
/*   Updated: 2025/09/24 18:19:57 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*andorcmd(t_ms *ms, t_tokkind kind, t_ast *cmd1, t_ast *cmd2)
{
	t_ast	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ms_fatal(ms, "andorcmd");
	if (kind == T_AND_IF)
		cmd->kind = AST_AND;
	else if (kind == T_OR_IF)
		cmd->kind = AST_OR;
	cmd->u_pao.s_pao.left = cmd1;
	cmd->u_pao.s_pao.right = cmd2;
	return (cmd);
}

t_ast	*parseandor(t_ms *ms, int *i)
{
	t_ast	*cmd;
	int		kind;

	cmd = parsepipe(ms, i);
	if (ms->ret != MS_OK)
		return (NULL);
	kind = ms->cyc.vec[*i].kind;
	if (kind == T_AND_IF || kind == T_OR_IF)
	{
		*i += 1;
		cmd = andorcmd(ms, kind, cmd, parseandor(ms, i));
		if (ms->ret != MS_OK)
			return (NULL);
	}
	return (cmd);
}

static t_ast	*pipecmd(t_ms *ms, t_ast *cmd1, t_ast *cmd2)
{
	t_ast	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		ms_fatal(ms, "pipecmd");
	cmd->kind = AST_PIPE;
	cmd->u_pao.s_pao.left = cmd1;
	cmd->u_pao.s_pao.right = cmd2;
	return (cmd);
}

t_ast	*parsepipe(t_ms *ms, int *i)
{
	t_ast	*cmd;

	cmd = parsecmd(ms, i);
	if (ms->ret != MS_OK)
		return (NULL);
	if (ms->cyc.vec[*i].kind == T_PIPE)
	{
		*i += 1;
		cmd = pipecmd(ms, cmd, parsepipe(ms, i));
		if (ms->ret != MS_OK)
			return (NULL);
	}
	return (cmd);
}
