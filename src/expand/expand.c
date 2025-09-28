/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:44:03 by echatela          #+#    #+#             */
/*   Updated: 2025/09/28 10:19:25 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp(char **arg, int i)
{
	
}

static char	*expand_str(char *arg)
{
	char	*exp_arg;
	int		i;
	int		in_sq;
	
	if (!strchr(arg, '$'))
		return (NULL);
	i = 0;
	in_sq = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			in_sq = !in_sq;
		while (arg[i] == '$' && !in_sq)
			exp(&arg, i);
	}
}

void	expand(t_ms *ms, t_cmd *cmd)
{
	char	*exp_arg;
	int		i;

	i = 0;
	while (cmd->argv.data[i])
	{
		exp_arg = expand_str(cmd->argv.data[i]);
	}
	expand_redv(ms, &cmd->redv);
}
