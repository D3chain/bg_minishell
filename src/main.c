/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:39 by echatela          #+#    #+#             */
/*   Updated: 2025/09/30 16:18:02 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigstate = 0;

static int	ms_init(t_ms *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_ms));
	ft_bzero(&ms->cyc, sizeof(t_cycle));
	if (ft_create_lstenvp(ms, envp) != MS_OK)
		return (ms_fatal(ms, "env_init"), MS_ERR);
	return (MS_OK);
}

static int	ms_iter(t_ms *ms)
{
	t_ret	r;

	r = ms_readline(ms);
	if (r != MS_OK)
		return (r);
	if (ms_lexer_parser(ms) != MS_OK)
		return (free(ms->cyc.line), MS_ERR);
	// ms_process(ms);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	int		i;

	(void)argc;
	(void)argv;
	if (ms_init(&ms, envp) != MS_OK)
		return (MS_ERR);
	i = 0;
	while (i < 3)
	{
		if (ms_iter(&ms) == MS_SIGINT)
			break ;
		ms_clear_cycle(&ms);
		i++;
	}
	ms_cleanup_all(&ms);
	return (ms.status);
}
