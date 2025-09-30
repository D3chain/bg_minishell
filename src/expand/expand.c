/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 12:44:03 by echatela          #+#    #+#             */
/*   Updated: 2025/09/29 12:39:35 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	q_handle(char c, int *i, t_sb *cur)
{
	if (c == '\'' && !cur->in_dq)
	{
		cur->in_sq = !cur->in_sq;
		*i++;
		return (1);
	}
	if (c == '\"' && !cur->in_sq)
	{
		cur->in_dq = !cur->in_dq;
		*i++;
		return (1);
	}
	return (0);
}

static int	expand_one(t_ms *ms, const char *arg, void *out, int argred)
{
	t_sb	cur;
	char	*out_str;
	int		i;

	if (sb_init(&cur) != MS_OK)
		ms_fatal(ms, "expand");
	i = 0;
	while (arg[i])
	{
		if (q_handle(arg[i], &i, &cur))
			continue ;
		if (arg[i] == '$' && !cur.in_sq)
		{
			sb_puts(&cur, read_var(ms, &arg[i], &cur, &i));
			continue ;
		}
		sb_putc(&cur, arg[i++]);
	}
	if (sb_detach_push(&cur, &out_str, out, argred) == MS_ERR)
		ms_fatal(ms, "expand");
	return (1);
}

static void	expand_argv(t_ms *ms, t_argvec *argv)
{
	t_argvec	out;
	size_t		i;

	i = 0;
	argvec_init(&out);
	while (i < argv->len)
	{
		const char	*arg = argv->data[i];
		if (!ft_strchr(arg, '$') && !ft_strchr(arg, '\'') && !ft_strchr(arg, '\"'))
			argvec_push_arg(&out, ft_strdup(arg));
		else
			expand_one(ms, arg, &out, 0);
	}
	argvec_free(argv);
	*argv = out;
}

static void	expand_redv(t_ms *ms, t_redirvec *redv)
{

}

void	expand(t_ms *ms, t_cmd *cmd)
{
	if (cmd->argv.data)
		expand_argv(ms, &cmd->argv);
	if (cmd->redv.data)
		expand_redv(ms, &cmd->redv);
}
