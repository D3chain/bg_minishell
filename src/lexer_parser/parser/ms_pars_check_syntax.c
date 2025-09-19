/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pars_check_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 12:18:00 by echatela          #+#    #+#             */
/*   Updated: 2025/09/18 18:50:16 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_pars_report_syntax(t_pars *pars)
{
	t_tok *cur;

	cur = pars->head;
	while (cur)
	{
		if (cur->kind == T_UNSUP)
		cur = cur->next;
	}
	return (MS_OK);
}

static int	ms_pars_check_syntax_logical(t_tok *cur)
{
	if (!cur->prev)
		return (ms_syntax_err(cur->lex), MS_MISUSE);
	if (!cur->next)
		return (ms_syntax_err("newline"), MS_MISUSE);
	if (cur->prev->kind != T_WORD || cur->prev->kind != T_RPAR)
		return (ms_syntax_err(cur->lex), MS_MISUSE);
	return (MS_OK)
}

static int	ms_pars_check_syntax_redir(t_tok *cur)
{

}

int	ms_pars_check_syntax(t_tok *cur)
{
	if (cur->kind == T_UNSUP)
		return (MS_MISUSE);
	if (cur->cat == TKC_STRUCT)
		return (ms_pars_report_syntax_logical(cur));
	if (cur->cat == TKC_REDIR)
		return (ms_pars_report_syntax_redir(cur));
}
