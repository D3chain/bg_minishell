/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:30:15 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:38:56 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ms_types.h"
# include "ms_lexer_parser.h"
# include "ms_ast.h"
# include "ms_tok.h"
# include "ms_stream.h"
# include "ms_error.h"

# include "libft.h"

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_ms
{
	char	**envp;
	char	*line;
	t_tok	*tok;
	t_ast	*ast;
	int		status;
	int		last_status;
}	t_ms;

// Core
char	*ms_term(t_ms *ms, char **envp);
void	ms_cleanup(t_ms *ms);



// Utils
char	*join_and_free(char *dst, char *join, int i);

#endif