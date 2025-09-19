/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:06:50 by echatela          #+#    #+#             */
/*   Updated: 2025/09/17 18:16:35 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cleanup(t_ms *ms)
{
	if (ms->line)
	{
		free(ms->line);
		ms->line = NULL;
	}
	if (ms->tok)
		ms_tokclear(ms->tok);
}