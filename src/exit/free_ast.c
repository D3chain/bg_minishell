/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:24:05 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 14:31:55 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_ast *cmd)
{
	if (cmd->u_pao.cmd.redv.data)
		redirvec_free(&cmd->u_pao.cmd.redv);
	if (cmd->u_pao.cmd.argv.data)
		argvec_free(&cmd->u_pao.cmd.argv);
	if (cmd->u_pao.cmd.fd[0] != -1)
		close(cmd->u_pao.cmd.fd[0]);
	if (cmd->u_pao.cmd.fd[1] != -1)
		close(cmd->u_pao.cmd.fd[1]);
	if (cmd->u_pao.cmd.hd_fd[0] != -1)
		close(cmd->u_pao.cmd.hd_fd[0]);
	if (cmd->u_pao.cmd.hd_fd[1] != -1)
		close(cmd->u_pao.cmd.hd_fd[1]);
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
