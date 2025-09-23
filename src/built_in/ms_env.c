/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:40 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 15:35:33 by garivoir         ###   ########.fr       */
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
int	ms_env(char **cmd, t_envp *envp)
{
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "env") != 0)
		return (-1);	//error
	if (!envp)
		return (0);
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
}
