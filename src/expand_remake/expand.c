/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:12:46 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 13:30:36 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unquote_str(t_ms *ms, char **str, int in_sq, int in_dq)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(*str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (*str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (*str[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		else if (i == j)
			j++;
		else
			*str[j++] = *str[i];
		i++;
	}
	while (j < len)
		*str[j++] = 0;
}

static void	expand_unquote(t_ms *ms, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->argv.len)
	{
		unquote_str(ms, &cmd->argv.data[i], 0, 0);
		i++;
	}
	i = 0;
	while (i < cmd->redv.len)
	{
		unquote_str(ms, &cmd->redv.data[i].word, 0, 0);
		i++;
	}
}

void	expand_wc(t_ms *ms, t_cmd *cmd)
{
	t_argvec	exp_argv;
	t_redirvec	exp_redv;

	argvec_init(&exp_argv);
	redirvec_init(&exp_redv);
}

void	expand(t_ms *ms, t_cmd *cmd)
{
	expand_var(ms, cmd);
	expand_wc(ms, cmd);
	word_split(ms, cmd);
	expand_unquote(ms, cmd);
}
