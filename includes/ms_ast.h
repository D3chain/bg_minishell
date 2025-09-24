/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:11:56 by echatela          #+#    #+#             */
/*   Updated: 2025/09/24 10:24:51 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_AST_H
# define MS_AST_H

typedef enum e_ast_nodekind
{
	AST_CMD,
	AST_PIPE,
	AST_AND,
	AST_OR
}	t_ast_nodekind;

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
		}	s_pao;
		t_cmd	cmd;
	}	u_pao;
}	t_ast;

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

int		is_quote_in(char *s);

#endif
