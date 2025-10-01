/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_term.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 08:38:44 by echatela          #+#    #+#             */
/*   Updated: 2025/09/30 19:01:08 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include "ms_types.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*ms_prompt_make(t_ms *ms, t_env *env);
void	ms_readline(t_ms *ms);

#endif