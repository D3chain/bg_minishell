/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:46:17 by echatela          #+#    #+#             */
/*   Updated: 2025/09/18 15:41:37 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_prompt(char *minishell, char *cwd)
{
	char	*prompt;
	int		tot_len;
	int		i;
	int		j;

	tot_len = ft_strlen(minishell) + ft_strlen(cwd) + 2;
	prompt = (char *)malloc(sizeof(char) * (tot_len + 1));
	if (!prompt)
		return (NULL);
	i = 0;
	j = 0;
	while (i < tot_len && minishell[j])
		prompt[i++] = minishell[j++];
	j = 0;
	while (i < tot_len && cwd[j])
		prompt[i++] = cwd[j++];
	prompt[i++] = '$';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	free(cwd);
	return (prompt);
}

static char	*find_cwd_in_path(t_ms *ms, char **envp)
{
	char	*cwd;
	int		i;

	cwd = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			cwd = ft_strdup(envp[i] + 4);
			if (!cwd)
				return (ms->status = MS_ERR, NULL);
			break ;
		}
		i++;
	}
	if (cwd && cwd[0])
		return (cwd);
	return (NULL);
}

static char	*ms_prompt(t_ms *ms, char **envp)
{
	char	*cwd;
	char	*prompt;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = find_cwd_in_path(ms, envp);
	if (!cwd && ms->status == MS_ERR)
		return (NULL);
	if (!cwd)
		cwd = ft_strdup("");
	if (!cwd)
		return (ms->status = MS_ERR, NULL);
	prompt = join_prompt("minishell:", cwd);
	if (!prompt)
		return (ms->status = MS_ERR, NULL);
	return (prompt);
}

char *ms_term(t_ms *ms, char **envp)
{
	char	*prompt;
	char	*line;

	prompt = ms_prompt(ms, envp);
	if (!prompt)
		return (ms->status = MS_ERR, NULL);
	line = readline(prompt);
	if (!line)
		return (ms->status = MS_ERR, NULL);
	free(prompt);
	add_history(line);
	return (line);
}
