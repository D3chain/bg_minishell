/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:44 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:47:09 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* export built-in				*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Print "envp" variable		*/
/*------------------------------*/
static void	ft_export_print_envp(t_env *envp)
{
	while (envp->next)
	{
		printf("declare -x %s=\"%s\"\n", envp->key, envp->val);
		envp = envp->next;
	}
	while (envp->prev)
		envp = envp->prev;
}

/*------------------------------*/
/* Make bubble sort by			*/
/* alphabatcical order for		*/
/* "envp", then print variable	*/
/*------------------------------*/
static void	ft_export_bubble_sort(t_env *envp)
{
	t_env	*temp1;
	t_env	*temp2;
	t_env	*temp3;

	temp1 = envp;
	while (temp1 && temp1->next)
	{
		if (ft_strcmp(temp1->key, temp1->next->key) > 0)
		{
			temp2 = temp1;
			temp3 = temp1->next;
			temp1 = temp3;
			temp1->next = temp2;
			temp1->prev = temp2->prev;
			temp1->next->prev = temp3->prev;
			temp1->next->next = temp3->next;
			if (temp1->prev)
				temp1 = temp1->prev;
		}
		else
			temp1 = temp1->next;
	}
	while(temp1->prev)
		temp1 = temp1->prev;
	ft_export_printf_envp(temp1);
}

/*------------------------------*/
/* Sort "envp" chained list		*/
/* by alphabetical order, and	*/
/* display variables on screen	*/
/*------------------------------*/
static int	ms_export_alphabetical(t_env *envp)
{
	if (!envp || !envp->var)
		return (-1);	//error
	if (!envp->next)
	{
		ft_export_print_envp(envp);
		return (0);
	}
	ft_export_bubble_sort(envp);
	return (0);
}

/*------------------------------*/
/* minishell export				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_export(char **cmd, t_env *envp)
{
	int	i;
	
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "export") != 0)
		return (-1);	//error
	if (envp == NULL)
		return (-1);	//error
	if (!cmd[1])
		return(ms_export_alphabetical(envp));
	while (envp->next)
		envp = envp->next;
	i = 1;
	while (cmd[i])
	{
		envp->next = ft_new_envp(cmd[i]);
		if (!envp->next)
			return (-1);	//error
		envp->next->prev = envp;
		envp->next->next = NULL;
		i++;
	}
	while (envp->prev)
		envp = envp->prev;
	return (0);
}
