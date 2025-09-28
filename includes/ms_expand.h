/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 15:07:04 by echatela          #+#    #+#             */
/*   Updated: 2025/09/28 15:47:21 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXPAND_H
# define MS_EXPAND_H

# define SB_BUF_SIZE	128

typedef struct s_sb
{
	char	*s;
	int		i;
	int		in_sq;
	int		in_dq;
	int		cap;
}	t_sb;

int	sb_init(t_sb *sb);

#endif