/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:39 by echatela          #+#    #+#             */
/*   Updated: 2025/10/01 11:09:37 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_init(t_ms *ms, char **envp)
{
	ft_bzero(ms, sizeof(t_ms));
	if (ft_create_lstenvp(ms, envp) != MS_OK)
		return (ms_fatal(ms, "env_init"), MS_ERR);
	return (MS_OK);
}

static int	ms_iter(t_ms *ms)
{
	ft_bzero(&ms->cyc, sizeof(ms->cyc));
	init_signals();
	g_sigstate = 0;
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
		return (MS_ERR);
	// ms_process(ms);
	return (MS_OK);
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
		if (ms_iter(&ms) == MS_SIGQUIT)
			break ;
		ms_clear_cycle(&ms);
		i++;
	}
	printf("Status: %d\n", ms.status);
	ms_cleanup_all(&ms);
	return (ms.status);
}
