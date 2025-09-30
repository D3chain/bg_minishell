/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 11:25:19 by echatela          #+#    #+#             */
/*   Updated: 2025/09/30 16:34:16 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ms_expand.h"

static void	not_dolar(t_ms *ms, t_sb *sb, char c, int *i)
{
	if (c == '\'' && !sb->in_dq)
		sb->in_sq = !sb->in_sq;
	else if (c == '\"' && !sb->in_sq)
		sb->in_dq = !sb->in_dq;
	else
		sb_putc(ms, sb, c);
	*i += 1;
}

static void	dolar(t_ms *ms, t_sb *sb, const char *arg, int *i)
{
	int		n;
	t_env	*cur;

	*i += 1;
	if (arg[*i] == '?')
		return (*i += 1, sb_puts(ms, sb, ft_itoa(ms->status)));
	if (!ft_isalpha(arg[*i]) && arg[*i] != '_')
		return (sb_putc(ms, sb, '$'));
	n = 0;
	while (arg[*i + n] && (ft_isalnum(arg[*i + n]) || arg[*i + n] == '_'))
		n++;
	cur = ms->env;
	while (cur)
	{
		if (ft_strncmp(&arg[*i], cur->key, n) == 0)
			return (*i += n, sb_puts(ms, sb, cur->val));
		cur = cur->next;
	}
	*i += n;
}

static void	expand_one(t_ms *ms, char **out, int is_hd)
{
	t_sb		sb;
	const char	*arg;
	int			i;

	init_sb(&sb);
	i = 0;
	arg = *out;
	while (arg[i])
	{
		if (arg[i] != '$' || is_hd || sb.in_sq || sb.in_dq)
			not_dolar(ms, &sb, arg[i], &i);
		else
			dolar(ms, &sb, arg, &i);
	}
	printf("%s\n", sb.buf);
	sb_add_reset_buf(ms, &sb);
	free(*out);
	*out = sb.out;
}

void	expand(t_ms *ms, t_cmd *cmd)
{
	int	i;

	if (cmd->argv.data)
	{
		i = 0;
		while (i < cmd->argv.len)
		{
			expand_one(ms, &cmd->argv.data[i], 0);
			i++;
		}
	}
	if (cmd->redv.data)
	{
		i = 0;
		while (i < cmd->redv.len)
		{
			if (cmd->redv.data[i].kind == AST_H_DOC)
				expand_one(ms, &cmd->redv.data[i].word, 1);
			else
				expand_one(ms, &cmd->redv.data[i].word, 0);
			i++;
		}
	}
}
