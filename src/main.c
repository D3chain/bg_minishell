/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:39 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 13:54:18 by echatela         ###   ########.fr       */
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
	init_sig(0);
	g_sigstate = 0;
}

static int	signal_quit(t_ms *ms, int sig)
{
	if (!ms->cyc.line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (MS_EOF);
	}
	if (sig == SIGINT)
	{
		ms->status = 128 + SIGINT;
		return (MS_SIGINT);
	}
	return (MS_OK);
}

static int	ms_iter(t_ms *ms)
{
	init_cycle(ms);
	ms_readline(ms);
	if (g_sigstate != 0 || !ms->cyc.line)
		return (signal_quit(ms, g_sigstate));
	if (!*ms->cyc.line)
		return (MS_OK);
	if (ms_lexer_parser(ms) != MS_OK)
		return (MS_MISUSE);
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
		if (ms_iter(&ms) == MS_EOF)
			break ;
		ms_clear_cycle(&ms);
	}
	ms_cleanup_all(&ms);
	return (ms.status);
}
