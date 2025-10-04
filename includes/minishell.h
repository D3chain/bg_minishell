/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:15 by echatela          #+#    #+#             */
/*   Updated: 2025/10/04 13:10:17 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_env.h"
# include "ms_signal.h"
# include "ms_term.h"
# include "ms_lexer_parser.h"
# include "ms_tok.h"
# include "ms_ast.h"
# include "ms_child.h"
# include "ms_expand.h"
# include "ms_built_in.h"
# include "ms_error.h"

# include "libft.h"

typedef struct s_cycle
{
	int		ret;
	char	*line;

	t_tok	*vec;
	int		tlen;
	int		in_sq;
	int		in_dq;

	t_ast	*ast;
}	t_cycle;

typedef struct s_ms
{
	int			status;
	
	t_env		*env;
	char		**envp_cache;
	int			envp_dirty;

	char		**path_dirs;
	int			path_dirty;

	t_cycle		cyc;
}	t_ms;

void	ms_clear_cycle(t_ms *ms);
void	ms_cleanup_all(t_ms *ms);


void	close_pair(int *fd);

int	is_quote_in_str(char *s);

#endif