/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:34 by echatela          #+#    #+#             */
/*   Updated: 2025/09/18 15:42:40 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(int c)
{
	return (c == ' ' || c == '\t' || (c >= 9 && c <= 13));
}

int	is_meta(int c)
{
	const int meta[] = {'|', '&', ',', '(', ')', '<', '>', 0};
	int	i;
	
	i = 0;
	while (meta[i])
	{
		if (c == meta[i])
			return (meta[i]);
		i++;
	}
	return (false);
}
