/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:36:54 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 23:43:29 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_ast_add_cmd(t_ms *ms, t_ast **node)
{
	if (!ms->cyc.ast)
		ms->cyc.ast = *node;
	
}

t_ret	ms_parser(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->cyc.vec[i - 1].cat != TKC_EOF)
	{
		if (ms->cyc.vec[i].cat == TKC_REDIR || ms->cyc.vec[i].cat == TKC_WORD)
			return (ms_syntax_err(ms->cyc.vec[i].lex), MS_MISUSE);
		ms_pars_cmd(ms, ms->cyc.vec, &i);
	}
	return(MS_OK);
}
