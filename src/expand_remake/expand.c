/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:12:46 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 18:31:45 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void _expand_var(t_ms *ms, t_cmd *cmd)
{
	t_argvec	exp_argv;
	t_redirvec	exp_redv;

	argvec_init(&exp_argv);
	redirvec_init(&exp_redv);

}

static void	_expand_wc(t_ms *ms, t_cmd *cmd)
{
	t_argvec	exp_argv;
	t_redirvec	exp_redv;

	argvec_init(&exp_argv);
	redirvec_init(&exp_redv);
}

void	expand(t_ms *ms, t_cmd *cmd)
{
	_expand_var(ms, cmd);
	_expand_wc(ms, cmd);
}
