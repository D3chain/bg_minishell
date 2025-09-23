/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:11:31 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 12:48:22 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ret	ms_lexer_parser(t_ms *ms)
{
	// t_ast	*ast;
	t_ret	r;

	r = ms_lexer(ms);
	if (r != MS_OK)
		return (r);
	// ast = ms_parser(ms, head);
	// if (!ast)
	// 	return (NULL);
	return (r);
}
