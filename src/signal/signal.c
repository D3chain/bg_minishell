/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:27:44 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 16:01:40 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sigstate = 0;

static void sigint_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (sig == SIGINT)
	{
		g_sigstate = sig;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	hd_sigint_handler(int sig, siginfo_t *info, void *ctx)
{
	(void)info;
	(void)ctx;
	if (sig == SIGINT)
	{
		g_sigstate = sig;
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void init_sig(int mode)
{
	struct sigaction sa;

	g_sigstate = 0;
	if (mode == 0)
		sa.sa_sigaction = sigint_handler;
	if (mode == 1)
		sa.sa_sigaction = hd_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ign_sig()
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

int wstatus(int w)
{
	if (WIFSIGNALED(w))
		return (128 + WTERMSIG(w));
	if (WIFEXITED(w))
		return (WEXITSTATUS(w));
	return (1);
}


