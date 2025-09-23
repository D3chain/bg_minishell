/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:27:18 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:47:28 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	argvec_init(t_argvec *v)
{
	v->data = NULL;
	v->len = 0;
	v->cap = 0;
}

void	argvec_free(t_argvec *v)
{
	int	i;

	if (!v || !v->data)
	{
		if (v)
			argvec_init(v);
		return ;
	}
	i = 0;
	while (i < v->len)
	{
		free(v->data[i]);
		i++;
	}
	free(v->data);
	argvec_init(v);
}

static int	argvec_grow(t_argvec *v, int need)
{
	int		ncap;
	char	**p;
	
	if (v->cap == 0)
		v->cap = 16;
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
	p = (char **)ms_realloc_array(v->data,
		(size_t)v->cap, (size_t)ncap, sizeof(*p));
	if (!p)
		return (0);
	v->data = p;
	v->cap = ncap;
	return (1);
}

int	argvec_reserve(t_argvec *v, int need)
{
	if (need < 0)
		return (0);
	if (v->cap >= need)
		return (1);
	return (argvec_grow(v, need));
}

int	argvec_push_arg(t_argvec *v, const char *arg)
{
	char	*tmp;

	if (!argvec_reserve(v, v->len + 1))
		return (MS_ERR);
	tmp = ft_strdup(arg);
	if (!tmp)
		return (MS_ERR);
	v->data[v->len++] = tmp;
	return (MS_OK);
}
