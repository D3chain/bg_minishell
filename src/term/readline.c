/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:20:33 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 16:35:05 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_readline(t_ms *ms)
{
	char	*prompt;
	char	*line;
	t_ret	r;
	
	r = ms_prompt_make(&prompt, ms->env);
	if (r != MS_OK)
		return (r);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (MS_EOF);
	if (*line != '\0')
		add_history(line);
	ms->cyc.line = line;
	return (MS_OK);
}
