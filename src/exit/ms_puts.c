/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:07:08 by echatela          #+#    #+#             */
/*   Updated: 2025/09/18 20:56:17 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "err.h"

int	fill1(char *buf, const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		ft_memcpy(buf, s, ft_strlen(s));
		i += ft_strlen(s);
	}
	return (i);
}

int	fill2(char *buf, const char *a, const char *b)
{
	int	i;

	i = 0;
	if (a)
		i += fill1(buf, a);
	if (b)
		i += fill1(buf + i, b);
	return (i);
}

int	fill3(char *buf, const char *a, const char *b, const char *c)
{
	int	i;

	i = 0;
	if (a)
		i += fill1(buf, a);
	if (b)
		i += fill1(buf + i, b);
	if (c)
		i += fill1(buf + i, c);
	return (i);
}
