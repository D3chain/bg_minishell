/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:11:56 by echatela          #+#    #+#             */
/*   Updated: 2025/09/27 13:26:07 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_AST_H
# define MS_AST_H

typedef enum e_ast_kind
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR,
	AST_R_IN,
	AST_H_DOC,
	AST_R_OUT,
	AST_R_APP
}	t_ast_kind;

typedef struct s_argvec
{
	char	**data;
	int		len;
	int		cap;
}	t_argvec;

typedef struct s_redirvec
{
	t_redir	*data;
	int		len;
	int		cap;
}	t_redirvec;

typedef struct e_redir
{
	t_ast_kind	kind;
	char		*word;
	int			quoted_delim;
}	t_redir;

typedef struct s_cmd
{
	t_argvec	argv;
	t_redirvec	redv;
}	t_cmd;

typedef struct s_ast
{
	t_ast_kind	kind;
	union
	{
		struct
		{
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_pao;
		t_cmd	cmd;
	}	u_pao;
}	t_ast;

void	free_ast(t_ms *ms);

// argvec
void	argvec_init(t_argvec *v);
void	argvec_free(t_argvec *v);
int		argvec_reserve(t_argvec *v, int need);
int		argvec_push_arg(t_argvec *v, const char *arg);

// redirvec
void	redirvec_init(t_redirvec *v);
void	redirvec_free(t_redirvec *v);
int		redirvec_reserve(t_redirvec *v, int need);
int		redirvec_push_redir(t_redirvec *v, const t_redir *t);

#endif
