/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_term.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 08:38:44 by echatela          #+#    #+#             */
/*   Updated: 2025/09/21 14:39:16 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include "ms_types.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

t_ret	ms_prompt_make(char **out_prompt, t_env *env);
t_ret	ms_readline(t_ms *ms);

#endif