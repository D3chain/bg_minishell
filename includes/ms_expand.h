/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:07:04 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 08:03:14 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXPAND_H
# define MS_EXPAND_H

#define BUFFER_SIZE	128

typedef struct s_sb
{
	char	*out;
	char	buf[BUFFER_SIZE];
	int		i;
	int		in_sq;
	int		in_dq;
}	t_sb;

void	expand(t_ms *ms, t_cmd *cmd);
void	expand_one(t_ms *ms, char **out, int is_hd);
void	init_sb(t_sb *sb);
void	sb_putc(t_ms *ms, t_sb *sb, char c);
void	sb_puts(t_ms *ms, t_sb *sb, const char *s);
void	sb_add_reset_buf(t_ms *ms, t_sb *sb);

#endif