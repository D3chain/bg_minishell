/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:41:46 by garivoir          #+#    #+#             */
/*   Updated: 2025/09/23 12:03:08 by echatela         ###   ########.fr       */
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
	if ((*envp)->var)
		free((*envp)->var);
	if ((*envp)->key)
		free((*envp)->key);
	if ((*envp)->val)
		free((*envp)->val);
	if ((*envp)->prev)
		(*envp)->prev = NULL;
	if ((*envp)->next)
		(*envp)->next = NULL;
	if (*envp)
		free(*envp);
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
		i = (int)ft_strlen(var);
		while (i >= 0 && var[i] != '=')
		{
			i--;
			size++;
		}
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
	envp->var = malloc(sizeof(ft_strlen(var) + 1));
	if (!envp->var)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	i = -1;
	while (var[++i])
		envp->var[i] = var[i];
	envp->var[++i] = 0;
	envp->key = malloc(sizeof(ft_equal_sign(var, 0) + 1));
	if (!envp->key)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	envp->val = malloc(sizeof(ft_equal_sign(var, 1) + 1));
	if (!envp->val)
		return (ft_free_envp_struct(&envp, -1), NULL);	//error
	ft_envp_var_name_and_value(envp);
	envp->prev = NULL;
	envp->next = NULL;
	return (envp);
}
