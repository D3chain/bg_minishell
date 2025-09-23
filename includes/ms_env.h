/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 08:38:57 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:29:11 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

# include "ms_types.h"

typedef struct s_env
{
	char			*var;
	char			*key;
	char			*val;
	
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

#endif