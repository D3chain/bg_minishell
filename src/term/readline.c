/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:20:33 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 10:54:37 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_readline(t_ms *ms)
{
	char	*prompt;
	
	prompt = ms_prompt_make(ms, ms->env);
	ms->cyc.line = readline(prompt);
	free(prompt);
	if (!ms->cyc.line || g_sigstate == SIGINT)
		return ;
	if (*ms->cyc.line != '\0')
		add_history(ms->cyc.line);
}
