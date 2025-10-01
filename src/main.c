/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:39 by echatela          #+#    #+#             */
/*   Updated: 2025/10/01 20:55:13 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_init(t_ms *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_ms));
	if (ft_create_lstenvp(ms, envp) != MS_OK)
		ms_fatal(ms, "env_init");
}

static void	init_cycle(t_ms *ms)
{
	ft_bzero(&ms->cyc, sizeof(ms->cyc));
	init_signals();
	g_sigstate = 0;
}

static int	ms_iter(t_ms *ms)
{
	init_cycle(ms);
	ms_readline(ms);
	if (!ms->cyc.line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		ms->status = 128 + SIGQUIT;
		return (MS_SIGQUIT);
	}
	if (!*ms->cyc.line)
		return (MS_OK);
	if (ms_lexer_parser(ms) != MS_OK)
		return (MS_MISUSE);
	if (ms->cyc.ret == MS_EOF)
		return (MS_EOF);
	// ms_process(ms);
	return (MS_OK);
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void)argc;
	(void)argv;
	ms_init(&ms, envp);
	while (1)
	{
		if (ms_iter(&ms) == MS_SIGQUIT)
			break ;
		ms_clear_cycle(&ms);
	}
	printf("Status: %d\n", ms.status);
	ms_cleanup_all(&ms);
	return (ms.status);
}
