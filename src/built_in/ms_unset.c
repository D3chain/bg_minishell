/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:50 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:48:34 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* unset built-in				*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Delete variable				*/
/* named unset's argument		*/
/*------------------------------*/
static void	ms_unset_delete_var(t_env *envp)
{
	t_env	*temp1;
	t_env	*temp2;

	temp1 = envp->prev;
	temp2 = envp->next;
	ft_free_envp_struct(&envp, 0);
	if (!temp1)
	{
		envp = temp2;
		envp->prev = temp1;
	}
	else
	{
		envp = temp1;
		envp->next = temp2;
	}
}

/*------------------------------*/
/* Create new "envp"			*/
/* after unset built-in			*/
/*------------------------------*/
static void	ms_unset_new_envp(char *cmd, t_env *envp)
{
	if (!envp)
		return ;
	while (envp->next)
	{
		if (ft_strcmp(cmd, envp->key) == 0)
		{
			ms_unset_delete_var(envp);
			while (envp->prev)
				envp = envp->prev;
			return ;
		}
		envp = envp->next;
	}
	while (envp->prev)
		envp = envp->prev;
	return ;
}

/*------------------------------*/
/* minishell unset				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_unset(char **cmd, t_env *envp)
{
	int	i;
	
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "unset") != 0)
		return (-1);	//error
	if (!cmd[1])
		return (0);
	i = 1;
	while (cmd[i])
		ms_unset_new_envp(cmd[i++], envp);
	return (0);
}
