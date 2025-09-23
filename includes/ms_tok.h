/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tok.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:10:21 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 13:01:48 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TOK_H
# define MS_TOK_H

# include "ms_types.h"

typedef enum e_tokcat
{
	TKC_WORD,
	TKC_REDIR,
	TKC_STRUCT,
	TKC_EOF
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
	T_EOF,
	T_UNSUP
}	t_tokkind;

typedef struct s_tok
{
	t_tokcat		cat;
	t_tokkind		kind;
	char			*lex;
}	t_tok;

typedef struct s_tokvec
{
	t_tok	*data;
	int		len;
	int		cap;
}	t_tokvec;

void	*ms_realloc_array(void *ptr, size_t old_n, size_t new_n, size_t elem_size);

/* core */
void	tokv_init(t_tokvec *v);
void	tokv_free(t_tokvec *v);
int		tokv_reserve(t_tokvec *v, int need);

/* push */
int		tokv_push_tok(t_tokvec *v, const t_tok *tok);

/* utils */
int		tokv_add_eof(t_tokvec *v);        /* ajoute TOK_EOF (unique) */

#endif
