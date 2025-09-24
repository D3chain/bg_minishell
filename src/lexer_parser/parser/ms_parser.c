/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:36:54 by echatela          #+#    #+#             */
/*   Updated: 2025/09/24 17:25:01 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parseblock(t_ms *ms, int *i)
{
	t_ast	*cmd;
	
	*i += 1;
	cmd = parsetokens(ms, i);
	if (ms->ret != MS_OK)
		return (NULL);
	if (ms->cyc.vec[*i].kind != T_RPAR)
		return (ms_syntax_err(ms->cyc.vec[*i].lex), ms->ret = MS_MISUSE, NULL);
	*i += 1;
	return (cmd);
}

t_ast	*parsetokens(t_ms *ms, int *i)
{
	t_ast	*cmd;

	cmd = parseandor(ms, i);
	return (cmd);
}

t_ret	ms_parser(t_ms *ms)
{
	t_ast	*head;
	int		i;

	i = 0;
	head = parsetokens(ms, &i);
	if (!head)
		return (MS_ERR);
	ms->cyc.ast = head;
	return (MS_OK);
}
