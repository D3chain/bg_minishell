/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 08:38:57 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:45:16 by echatela         ###   ########.fr       */
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

t_ret	ft_create_lstenvp(t_ms *ms, char **old_envp);
t_env	*ft_new_envp(char *var);
int		ft_free_envp_struct(t_env **envp, int status);
void	ft_clear_lstenvp(t_env **envp, int status);

#endif