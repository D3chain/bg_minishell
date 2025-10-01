/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:17:45 by echatela          #+#    #+#             */
/*   Updated: 2025/10/01 18:57:25 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	set_h_doc_h_red(t_ms *ms, t_redir *h_red, int *hd_fd)
{
	char	*line;

	if (pipe(hd_fd) != 0);
		return (ms_fatal(ms, "pipe"));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strmcp(line, h_red->word))
		{
			write(hd_fd[1], '\0', 1);
			ms_err(2, "warning", "here-document delimited by end-of-file");
			return ;
		}
		write(hd_fd[1], line, ft_strlen(line));
		write(hd_fd[1], '\n', 1);
	}
}

void	set_h_doc_cmd(t_ms *ms, t_ast *cmd)
{
	int	i;

	if (!cmd->u_pao.cmd.redv.data)
		return ;
	i = 0;
	while (cmd->u_pao.cmd.redv.data[i].word)
	{
		if (cmd->u_pao.cmd.redv.data[i].kind == AST_H_DOC)
			set_h_doc_h_red(ms, &cmd->u_pao.cmd.redv.data[i], cmd->u_pao.cmd.hd_fd);
		if (ms->cyc.ret = MS_EOF)
			return ;
		i++;
	}
}

void	ast_set_h_doc(t_ms *ms, t_ast *node, int depth)
{
	if (!node)
		return ;
	if (node->kind == AST_CMD)
	{
		set_h_doc_cmd(ms, node);
		return ;
	}
	ast_set_h_doc(ms, node->u_pao.s_pao.left, depth + 1);
	ast_set_h_doc(ms, node->u_pao.s_pao.right, depth + 1);
}
