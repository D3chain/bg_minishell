/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:25:21 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 17:28:19 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_exp_var(t_ms *ms, t_sb *sb, char *str, int *i)
{
	int		n;
	int		j;
	t_env	*cur;

	j = *i + 1;
	if (str[j] == '?')
		return (*i += 1, sb_puts(ms, sb, ft_itoa(ms->status)));
	if (!ft_isalpha(str[j]) && str[j] != '_')
		return (sb_putc(ms, sb, '$'));
	n = 0;
	while (str[j + n] && (ft_isalnum(str[j + n]) || str[j + n] == '_'))
		n++;
	cur = ms->env;
	while (cur)
	{
		if (ft_strncmp(&str[j], cur->key, n) == 0)
			return (*i += n, sb_puts(ms, sb, cur->val));
		cur = cur->next;
	}
	*i += n;
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
	sb_add_reset_buf(ms, &sb);
	return (sb.out);
}

static void	_exp_var_red(t_ms *ms, t_redir ref, t_redirvec *redv)
{
	t_redir	out;

	out.kind = ref.kind;
	out.quoted_delim = ref.quoted_delim;
	if (out.kind = AST_H_DOC)
		out.word = ft_strdup(ref.word);
	else
		out.word = exp_var_str(ms, ref.word);
	if (!out.word)
		ms_fatal(ms, "expand");
	if (redirvec_push_redir(redv, &out) == MS_ERR)
		ms_fatal(ms, "expand");
}

static void	_exp_var_arg(t_ms *ms, char *ref, t_argvec *argv)
{
	char	*out;

	out = exp_var_str(ms, ref);
	if (!out)
		ms_fatal(ms, "expand");	
	argvec_push_arg(argv, out);
}

void expand_var(t_ms *ms, t_cmd *cmd)
{
	t_argvec	exp_argv;
	t_redirvec	exp_redv;
	int			i;

	argvec_init(&exp_argv);
	redirvec_init(&exp_redv);
	i = -1;
	while (++i < cmd->argv.len)
		_exp_var_arg(ms, &cmd->argv.data[i], &exp_argv);
	i = -1;
	while (++i < cmd->redv.len)
		_exp_var_red(ms, cmd->redv.data[i], &exp_redv);
	argvec_free(&cmd->argv);
	redirvec_free(&cmd->redv);
	cmd->argv = exp_argv;
	cmd->redv = exp_redv;
}
