/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:39:48 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:14:55 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TYPES_H
# define MS_TYPES_H

typedef struct s_ms		t_ms;
typedef struct s_lex	t_lex;

typedef enum e_tokcat	t_tokcat;
typedef enum e_tokkind	t_tokkind;
typedef struct s_tok	t_tok;

typedef enum e_ast_nodekind		t_ast_nodekind;
typedef enum e_ast_andor_op		t_ast_andor_op;
typedef enum e_ast_redirkind	t_ast_redirkind;
typedef struct e_redir			t_redir;
typedef struct s_cmd			t_cmd;
typedef struct s_ast			t_ast;


#endif