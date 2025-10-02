/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:17:45 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 16:05:29 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static void	_hd_init(t_ms *ms, int *hd_fd)
{
	ms->cyc.ret = MS_OK;
	close_pair(hd_fd);
	if (pipe(hd_fd) != 0)
		ms_fatal(ms, "pipe hd");
}

static void	_here_doc(t_ms *ms, t_redir *h_red, int *hd_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sigstate == SIGINT || ft_strcmp(line, h_red->word) == 0 || !line)
		{
			close_pair(hd_fd);
			ms_cleanup_all(ms);
			if (g_sigstate == SIGINT)
				exit(MS_SIGINT);
			if (ft_strcmp(line, h_red->word) == 0)
				exit(MS_OK);
			if (!line)
			{
				ms_err(2, "warning", "here-document delimited by end-of-file");
				exit(MS_OK);
			}
		}
		if (!h_red->quoted_delim)
			expand_one(ms, &line, 0);
		write(hd_fd[1], line, ft_strlen(line));
		write(hd_fd[1], "\n", 1);
	}
}

void	here_doc(t_ms *ms, t_redir *h_red, int *hd_fd)
{
	pid_t	pid;
	int		st;

	st = 0;
	_hd_init(ms, hd_fd);
	pid = fork();
	if (pid == -1)
		ms_fatal(ms, "fork");
	if (pid == 0)
	{
		init_sig(1);
		_here_doc(ms, h_red, hd_fd);
	}
	ign_sig();
	waitpid(pid, &st, 0);
	if (wstatus(st) != 1)
		ms->cyc.ret = wstatus(st);
}
