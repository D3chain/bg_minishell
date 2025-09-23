/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:11:31 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:03:18 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_lexer_parser(t_ms *ms)
{
	t_ret	r;

	r = ms_lexer(ms);
	if (r != MS_OK)
		return (r);
	r = ms_parser(ms);
	if (r != MS_OK)
		return (r);
	return (r);
}
