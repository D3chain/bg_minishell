/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:40 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 12:04:34 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* env built-in					*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* minishell env				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_env(char **cmd, t_env *envp)
{
	if (!cmd || !cmd[0])
		return (MS_ERR);	//error
	if (ft_strcmp(cmd[0], "env") != 0)
		return (MS_ERR);	//error
	if (!envp)
		return (MS_OK);
	while (envp && envp->next)
	{
		if (envp->var)
			printf("%s", envp->var);
		envp = envp->next;
	}
	if (envp->var)
			printf("%s", envp->var);
	while (envp->prev)
		envp = envp->prev;
	return (MS_OK);
}
