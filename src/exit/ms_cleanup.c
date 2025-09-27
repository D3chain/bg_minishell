/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:06:50 by echatela          #+#    #+#             */
/*   Updated: 2025/09/27 12:40:45 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vec_free(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->cyc.tlen)
		if (ms->cyc.vec[i].lex)
			free(ms->cyc.vec[i++].lex);
	free(ms->cyc.vec);
}

void	ms_cleanup_all(t_ms *ms)
{
	ms_clear_cycle(ms);
}

void	ms_clear_cycle(t_ms *ms)
{
	if (ms->cyc.vec)
		vec_free(ms);
	if (ms->cyc.ast)
		free_ast(ms->cyc.ast);
	ft_bzero(&ms->cyc, sizeof(t_cycle));
}
