/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:25:21 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 14:44:16 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_exp_var(t_ms *ms, t_sb *sb, char *str, int *i)
{
	int		n;
	t_env	*cur;

	*i += 1;
	if (str[*i] == '?')
		return (*i += 1, sb_puts(ms, sb, ft_itoa(ms->status)));
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (sb)
}	

char	*exp_var_str(t_ms *ms, const char *str)
{
	t_sb	sb;
	int		i;

	init_sb(&sb);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !sb.in_dq)
		sb.in_sq = !sb.in_sq;
		else if (str[i] == '\"' && !sb.in_sq)
			sb.in_dq = !sb.in_dq;
		else if (str[i] == '$' && !sb.in_sq)
			_exp_var(ms, &sb, str, &i);
		else
			sb_putc(ms, &sb, str[i]);
		i++;
	}
}

static void	_exp_var_red(t_ms *ms, t_redir ref, t_redirvec *redv)
{
	t_redir	out;

	out.kind = ref.kind;
	out.quoted_delim = ref.quoted_delim;
	if (out.kind = AST_H_DOC)
		out.word = ft_strdup(ref.word);
	else
		out.word = exp_var_str(ref.word, );
	if (!out.word)
		ms_fatal(ms, "expand");
	free(ref.word);
	if (redirvec_push_redir(redv, &out) == MS_ERR)
		ms_fatal(ms, "expand");
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
