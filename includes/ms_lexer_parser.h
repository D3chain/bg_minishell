/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:15:01 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:15:47 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LEXER_H
# define MS_LEXER_H

# include "ms_types.h"

// Lexer_Parser
t_ret	ms_lexer_parser(t_ms *ms);

	// Lexer
t_ret	ms_lexer(t_ms *ms);
t_tok	ms_lex_read_get_tok(t_ms *ms, int *i);

		// Utils
int		is_blank(int c);
int		is_meta(int c);

	// Parser
t_ret	ms_parser(t_ms *ms);
int		ms_pars_check_syntax(t_tok *cur);

	// Utils
		// Token
t_tok	ms_create_tok(t_tokkind kind, char *s);

#endif