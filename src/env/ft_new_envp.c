/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:41:46 by garivoir          #+#    #+#             */
/*   Updated: 2025/09/23 15:19:33 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* New "envp"					*/
/* struct creation file			*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Free "envp" structure		*/
/*------------------------------*/
int	ft_free_envp_struct(t_env **envp, int status)
{
	if (!envp || !*envp)
		return (status);
	if ((*envp)->var)
		free((*envp)->var);
	if ((*envp)->key)
		free((*envp)->key);
	if ((*envp)->val)
		free((*envp)->val);
	free(*envp);
	*envp = NULL;
	return (status);	//error
}

/*------------------------------*/
/* Check if there is			*/
/* an '=' sign on the variable	*/
/*------------------------------*/
static int	ft_check_envp_var(char *var)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (var[i])
	{
		if (var[i] == '=')
			check = 1;
		i++;
	}
	if (check == 0)
		return (-1);	//error
	else
		return (0);
}

/*------------------------------*/
/* Check where the '=' sign		*/
/* is located, to allocate good	*/
/* memory size to each variable	*/
/*------------------------------*/
int	ft_equal_sign(char *var, int equal)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (equal == 0)
	{
		while (var[i] && var[i] != '=')
		{
			i++;
			size++;
		}
	}
	if (equal == 1)
	{
		i = 0;
		while (var[i] && var[i] != '=')
			i++;
		if (var[i] == '=')
			i++;
		while (var[++i])
			size++;
	}
	return (size);
}

/*------------------------------*/
/* Put name and value			*/
/* of each "envp" variable		*/
/* into two separate variables	*/
/*------------------------------*/
void	ft_envp_var_name_and_value(t_env *envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp->var[i] && envp->var[i] != '=')
	{
		envp->key[j] = envp->var[i];
		i++;
		j++;
	}
	envp->key[j] = 0;
	i++;
	j = 0;
	while (envp->var[i])
	{
		envp->val[j] = envp->var[i];
		i++;
		j++;
	}
	envp->val[j] = 0;
}

/*------------------------------*/
/* Create a new					*/
/* "envp" structure				*/
/*------------------------------*/
t_env	*ft_new_envp(char *var)
{
	int		i;
	t_env	*envp;

	if(ft_check_envp_var(var) != 0)
		return (NULL);								//error
	envp = malloc(sizeof(t_env));
	if (!envp)
		return (NULL);								//error
	envp->var = malloc(ft_strlen(var) + 1);
	if (!envp->var)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	i = -1;
	while (var[++i])
		envp->var[i] = var[i];
	envp->var[i] = '\0';
	envp->key = malloc(ft_equal_sign(var, 0) + 1);
	if (!envp->key)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	envp->val = malloc(ft_equal_sign(var, 1) + 1);
	if (!envp->val)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	ft_envp_var_name_and_value(envp);
	envp->prev = NULL;
	envp->next = NULL;
	return (envp);
}
