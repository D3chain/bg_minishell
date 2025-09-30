/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:13:53 by echatela          #+#    #+#             */
/*   Updated: 2025/09/29 12:50:22 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_var(t_ms *ms, const char *p_arg, t_sb *cur, int *i)
{
	char	*out;
	
	++*i;
	if (!ft_isalpha(p_arg[*i]) || p_arg[*i] != '_')
	{
		if (p_arg[*i] == ' ' || (p_arg[*i] >= 9 && p_arg[*i] <= 13))
		{
			out = ft_strdup("$");
		}
	}
	while (p_arg[*i])
	{
		
	}
	return (out);
}
