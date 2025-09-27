/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:44:03 by echatela          #+#    #+#             */
/*   Updated: 2025/09/27 15:06:38 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	expand(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv.data[i])
	{
		
	}
	expand_redv(ms, &cmd->redv);
}
