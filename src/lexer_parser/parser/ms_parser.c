/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:36:54 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:50:01 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_pars_cmd(t_ms *ms, t_tok *vec, int *i)
{
	t_cmd	cmd;

	while (vec[*i].cat == TKC_REDIR || vec[*i].cat == TKC_WORD)
	{
		if (vec[*i].cat == TKC_REDIR)
			ms_pars_redir()

	}
	return (MS_OK);
}

t_ret	ms_parser(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->cyc.vec[i - 1].cat != TKC_EOF)
	{
		if (ms_pars_cmd(ms, ms->cyc.vec, &i) != MS_OK)
			return (MS_ERR);
	}
	return(MS_OK);
}
