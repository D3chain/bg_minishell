/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:11:31 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 10:54:49 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_tok(t_ms *ms)
// {
// 	int	i = -1;

// 	while (++i < ms->cyc.tlen)
// 		printf("lexeme: %s\n", ms->cyc.vec[i].lex);
// }

static const char *kind_str(t_ast_kind k)
{
	if (k == AST_CMD)  return "CMD";
	if (k == AST_PIPE) return "PIPE";
	if (k == AST_AND)  return "AND";
	if (k == AST_OR)   return "OR";
	if (k == AST_R_IN)  return "R_IN";
	if (k == AST_H_DOC) return "H_DOC";
	if (k == AST_R_OUT) return "R_OUT";
	if (k == AST_R_APP) return "R_APP";
	return "?";
}

static const char *redir_str(t_ast_kind k)
{
	if (k == AST_R_IN)  return "<";
	if (k == AST_R_OUT) return ">";
	if (k == AST_R_APP) return ">>";
	if (k == AST_H_DOC) return "<<";
	return "?";
}

static void indent(int n)
{
	while (n-- > 0)
		write(1, "  ", 2);
}

static void ast_print_cmd(const t_cmd *c, int depth)
{
	int i;

	indent(depth);
	printf("NODE CMD:\n");

	indent(depth+1);
	printf("argc=%d\n", c->argv.len);

	i = 0;
	while (i < c->argv.len)
	{
		indent(depth+1);
		printf("argv[%d]: %s\n", i, c->argv.data[i]);
		i++;
	}
	i = 0;
	while (i < c->redv.len)
	{
		indent(depth+1);
		printf("redir[%d]: %s %s%s\n",
			i,
			redir_str(c->redv.data[i].kind),
			c->redv.data[i].word ? c->redv.data[i].word : "(null)",
			(c->redv.data[i].kind == AST_H_DOC && c->redv.data[i].quoted_delim) ? " (quoted)" : ""
		);
		i++;
	}
}

void ast_print(t_ms *ms, t_ast *node, int depth)
{
	if (!node)
	{
		indent(depth);
		printf("(null)\n");
		return;
	}
	if (node->kind == AST_CMD)
	{
		expand(ms, &node->u_pao.cmd);
		ast_print_cmd(&node->u_pao.cmd, depth);
		return;
	}
	/* nœuds binaires: PIPE / AND / OR */
	indent(depth);
	printf("NODE %s\n", kind_str(node->kind));

	indent(depth);
	printf("left:\n");
	ast_print(ms, node->u_pao.s_pao.left, depth + 1);

	indent(depth);
	printf("right:\n");
	ast_print(ms, node->u_pao.s_pao.right, depth + 1);
}

t_ret	ms_lexer_parser(t_ms *ms)
{
	if (ms_lexer(ms) == MS_MISUSE)
		return (MS_MISUSE);
	if (ms_parser(ms) == MS_MISUSE)
		return (MS_MISUSE);
	ast_print(ms, ms->cyc.ast, 0);
	return (MS_OK);
}
