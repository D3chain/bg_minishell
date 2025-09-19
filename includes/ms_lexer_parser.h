/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:01 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:40:18 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include "ms_types.h"

typedef struct s_lex
{
	const char	*src;
	int			i;
	int			in_sq;
	int			in_dq;
	t_tok		*vec;
}	t_lex;

typedef struct s_pars
{
	t_tok	*head;
	t_ast	*ast;
	int		st;
}	t_pars;

// Lexer_Parser
t_ast	*ms_lexer_parser(t_ms *ms, const char *line);

	// Lexer
t_tok	*ms_lexer(t_ms *ms, const char *line);
t_list	*ms_lex_read_get_node(t_ms *ms, t_lex *lex, t_list **lst);

		// Utils
int		is_blank(int c);
int		is_meta(int c);

	// Parser
t_ast	*ms_parser(t_ms *ms, t_tok *head);
int		ms_pars_check_syntax(t_tok *cur);

	// Utils
		// Token
t_tok	ms_create_tok(t_tokkind kind, char *s);
void	ms_tok_del(void *p);
void	ms_tokclear(t_tok *tok);

#endif