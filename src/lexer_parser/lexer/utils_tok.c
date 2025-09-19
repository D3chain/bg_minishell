/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:15:21 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:42:43 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok	ms_create_tok(t_tokkind kind, char *s)
{
	t_tok	tok;

	ft_bzero(&tok, sizeof(t_tok));
	if (kind == T_WORD)
		tok.cat = TKC_WORD;
	else if (kind >= T_PIPE && kind <= T_RPAR)
		tok.cat = TKC_STRUCT;
	else
		tok.cat = TKC_REDIR; 
	tok.kind = kind;
	tok.lex = s;
	return (tok);
}

void	ms_tok_del(t_tok *tok)
{
	if (!tok)
		return ;
	free(tok->lex);
}
