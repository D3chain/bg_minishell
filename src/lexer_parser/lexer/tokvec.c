/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:57:24 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 13:02:00 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokv_free_lexeme(t_tok *t)
{
	if (t->lex)
		free(t->lex);
}

void	tokv_init(t_tokvec *v)
{
	v->data = NULL;
	v->len = 0;
	v->cap = 0;
}

void	tokv_free(t_tokvec *v)
{
	int	i;

	if (!v || !v->data)
	{
		if (v)
			tokv_init(v);
		return ;
	}
	i = 0;
	while (i < v->len)
	{
		tokv_free_lexeme(&v->data[i]);
		i++;
	}
	free(v->data);
	tokv_init(v);
}

static int	tokv_grow(t_tokvec *v, int need)
{
	int		ncap;
	t_tok	*p;
	
	if (v->cap == 0)
		ncap = 16;
	else
		ncap = v->cap;
	while (ncap < need)
	{
		if (ncap > INT_MAX / 2)
		{
			ncap = need;
			break ;
		}
		ncap *= 2;
	}
	p = (t_tok *)ms_realloc_array(v->data,
		(size_t)v->cap, (size_t)ncap, sizeof(*p));
	if (!p)
		return (0);
	v->data = p;
	v->cap = ncap;
	return (1);
}

int	tokv_reserve(t_tokvec *tv, int need)
{
	if (need < 0)
		return (0);
	if (tv->cap >= need)
		return (1);
	return (tokv_grow(tv, need));
}
