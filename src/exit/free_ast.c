/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:24:05 by echatela          #+#    #+#             */
/*   Updated: 2025/09/27 13:51:49 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_ast *cmd)
{
	if (cmd->u_pao.cmd.redv.data)
		redirvec_free(&cmd->u_pao.cmd.redv);
	if (cmd->u_pao.cmd.argv.data)
		argvec_free(&cmd->u_pao.cmd.argv);
}

static void	free_node(t_ast *node)
{
	if (node->kind == AST_CMD)
		return (free_cmd(node), free(node));
	if (node->u_pao.s_pao.left)
		free_node(node->u_pao.s_pao.left);
	if (node->u_pao.s_pao.right)
		free_node(node->u_pao.s_pao.right);
	free(node);
}

void	free_ast(t_ms *ms)
{
	if (ms->cyc.ast)
		free_node(ms->cyc.ast);
}
