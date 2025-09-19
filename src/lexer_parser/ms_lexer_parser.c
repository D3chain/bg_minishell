/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:11:31 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 12:29:48 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ms_lexer_parser(t_ms *ms, const char *line)
{
	// t_ast	*ast;
	t_tok	*head;

	head = ms_lexer(ms, line);
	if (!head)
		return (NULL);
	// ast = ms_parser(ms, head);
	// if (!ast)
	// 	return (NULL);
	return (NULL);
}
