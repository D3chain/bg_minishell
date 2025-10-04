/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:25:21 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 13:52:07 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_exp_var_red(t_ms *ms, t_redir ref, t_redirvec *redv)
{
	
}

static void	_exp_var_arg()
{

}

static void	_exp_var(t_ms *ms, t_cmd *cmd, t_argvec *argv, t_redirvec *redv)
{
	int	i;

	i = 0;
	while (i < cmd->argv.len)
	{
		_exp_var_arg();
		i++;
	}
	i = 0;
	while (i < cmd->redv.len)
	{
		_exp_var_red(ms, cmd->redv.data[i], redv);
		i++;
	}
}

void expand_var(t_ms *ms, t_cmd *cmd)
{
	t_argvec	exp_argv;
	t_redirvec	exp_redv;

	argvec_init(&exp_argv);
	redirvec_init(&exp_redv);
}
