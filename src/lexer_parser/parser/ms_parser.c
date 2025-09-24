/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:36:54 by echatela          #+#    #+#             */
/*   Updated: 2025/09/24 11:15:29 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ms_ast_get_next_node(t_ms *ms)
{
	
}

t_ret	ms_ast_add_cmd(t_ms *ms, t_ast **node)
{
	if (!ms->cyc.ast)
		ms->cyc.ast = *node;
	
}

t_ast	*parsepipe(t_ms *ms, int *i)
{
	t_ast	*cmd;

	cmd = parsecmd(ms, i);
}

t_ast	*parseandor(t_ms *ms, int *i)
{
	t_ast	*cmd;

	cmd = parsepipe(ms, i);
}

t_ast	*parsetokens(t_ms *ms, int *i)
{
	t_ast	*cmd;
	int		i;

	i = 0;
	cmd = parseandor(ms, &i);

}

t_ret	ms_parser(t_ms *ms)
{
	t_ast	*head;
	int		i;

	i = 0;
	head = parsetokens(ms, &i);
	ms->cyc.ast = head;
	return (MS_OK);
}
