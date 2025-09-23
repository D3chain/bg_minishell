/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:11:56 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 18:48:28 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_AST_H
# define MS_AST_H

typedef enum e_ast_nodekind
{
	AST_CMD,
	AST_PIPE,
	AST_ANDOR
}	t_ast_nodekind;

typedef enum e_ast_andor_op
{
	AO_AND,
	AO_OR
}	t_ast_andor_op;

typedef enum e_ast_redirkind
{
	AST_R_IN,
	AST_H_DOC,
	AST_R_OUT,
	AST_R_APP
}	t_ast_redirkind;

typedef struct e_redir
{
	t_ast_redirkind	kind;
	char			*word;
	int				quoted_delim;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	int		argc;
	t_redir	*redirs;
	int		redir_count;
}	t_cmd;

typedef struct s_ast
{
	t_ast_nodekind	kind;
	union
	{
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_pipe;
		struct
		{
			t_ast_andor_op	op;
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_andor;
		t_cmd	cmd;
	}	u_pao;
}	t_ast;

typedef struct s_argvec
{
	char	**data;
	int		len;
	int		cap;
}	t_argvec;

void	argvec_init(t_argvec *v);
void	argvec_free(t_argvec *v);
int		argvec_reserve(t_argvec *v, int need);
int		argvec_push_arg(t_argvec *v, const char *arg);

#endif
