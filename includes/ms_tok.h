/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:10:21 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:30:40 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MS_TOK_H
# define MS_TOK_H

# include "ms_types.h"

typedef enum e_tokcat
{
	TKC_WORD,
	TKC_REDIR,
	TKC_STRUCT
}	t_tokcat;

typedef enum e_tokkind
{
	T_WORD,
	T_PIPE,
	T_OR_IF,
	T_AND_IF,
	T_LPAR,
	T_RPAR,
	T_RED_IN,
	T_H_DOC,
	T_RED_OUT,
	T_RED_APP,
	T_UNSUP
}	t_tokkind;

typedef struct s_tok
{
	t_tokcat		cat;
	t_tokkind		kind;
	char			*lex;
}	t_tok;

#endif
