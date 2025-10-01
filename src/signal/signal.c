/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:27:44 by echatela          #+#    #+#             */
/*   Updated: 2025/10/01 10:57:06 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


volatile sig_atomic_t g_sigstate = 0;

/* handler 3-args: on ne fait que marquer le flag (et optionnellement un '\n') */
static void sigint_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)info; (void)ctx;
	if (sig == SIGINT)
	{
		g_sigstate = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void init_signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void child_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	ms_status_from_wait(int w)
{
	if (WIFEXITED(w))
		return (WEXITSTATUS(w) & 0xFF);
	if (WIFSIGNALED(w))
		return (128 + (WTERMSIG(w) & 0x7F));
	return (1);
}
