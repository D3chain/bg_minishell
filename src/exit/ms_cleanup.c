/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:06:50 by echatela          #+#    #+#             */
/*   Updated: 2025/09/30 18:18:00 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	vec_free(t_ms *ms)
{
	int	i;

	i = 0;
	while (i < ms->cyc.tlen)
		if (ms->cyc.vec[i].lex)
			free(ms->cyc.vec[i++].lex);
	free(ms->cyc.vec);
}

static void	free_envp_cache(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->envp_cache[i])
	{
		free(ms->envp_cache[i]);
		i++;
	}
	free(ms->envp_cache);
}

void	ms_clear_cycle(t_ms *ms)
{
	if (ms->cyc.line)
		free(ms->cyc.line);
	if (ms->cyc.vec)
		vec_free(ms);
	if (ms->cyc.ast)
		free_ast(ms);
	ft_bzero(&ms->cyc, sizeof(t_cycle));
}

void	ms_cleanup_all(t_ms *ms)
{
	ms_clear_cycle(ms);
	if (ms->env)
		ft_clear_lstenvp(&ms->env, 0);
	if (ms->envp_cache)
		free_envp_cache(ms);
	rl_clear_history();
}
