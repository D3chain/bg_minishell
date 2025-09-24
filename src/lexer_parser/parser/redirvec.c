/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:27:18 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:47:28 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	redirvec_init(t_redirvec *v)
{
	v->data = NULL;
	v->len = 0;
	v->cap = 0;
}

void	redirvec_free(t_redirvec *v)
{
	int	i;

	if (!v || !v->data)
	{
		if (v)
			redirvec_init(v);
		return ;
	}
	i = 0;
	while (i < v->len)
	{
		if (v->data[i].word)
			free(v->data[i].word);
		i++;
	}
	free(v->data);
	redirvec_init(v);
}

static int	redirvec_grow(t_redirvec *v, int need)
{
	int		ncap;
	t_redir	*p;
	
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
	p = (t_redir *)ms_realloc_array(v->data,
		(size_t)v->cap, (size_t)ncap, sizeof(*p));
	if (!p)
		return (0);
	v->data = p;
	v->cap = ncap;
	return (1);
}

int	redirvec_reserve(t_redirvec *v, int need)
{
	if (need < 0)
		return (0);
	if (v->cap >= need)
		return (1);
	return (redirvec_grow(v, need));
}

int	redirvec_push_redir(t_redirvec *v, const t_redir *t)
{
	t_redir	tmp;

	if (!redirvec_reserve(v, v->len + 1))
		return (MS_ERR);
	tmp = *t;
	if (t->word)
	{
		tmp.word = ft_strdup(t->word);
		if (!tmp.word)
			return (MS_ERR);
	}
	else
		tmp.word = NULL;
	v->data[v->len++] = tmp;
	return (MS_OK);
}
