/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:41:46 by garivoir          #+#    #+#             */
/*   Updated: 2025/09/19 13:52:22 by garivoir         ###   ########.fr       */
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
int	ft_free_envp_struct(t_envp **envp, int status)
{
	if ((*envp)->var)
		free((*envp)->var);
	if ((*envp)->name)
		free((*envp)->name);
	if ((*envp)->value)
		free((*envp)->value);
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
		if (var[i] = '=')
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
	char	*str;

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
void	ft_envp_var_name_and_value(t_envp *envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp->var[i] && envp->var[i] != '=')
	{
		envp->name[j] = envp->var[i];
		i++;
		j++;
	}
	envp->name[j] = 0;
	i++;
	j = 0;
	while (envp->var[i])
	{
		envp->value[j] = envp->var[i];
		i++;
		j++;
	}
	envp->value[j] = 0;
}

/*------------------------------*/
/* Create a new					*/
/* "envp" structure				*/
/*------------------------------*/
t_envp	*ft_new_envp(char *var)
{
	int		i;
	t_envp	*envp;

	if(ft_check_envp_var(var) != 0)
		return (NULL);								//error
	i = 0;
	envp = malloc(sizeof(t_envp));
	if (!envp)
		return (NULL);								//error
	envp->var = malloc(sizeof(ft_strlen(var) + 1));
	if (!envp->var)
		return (ft_free_envp_struct(&envp, -1));	//error
	while (var[i])
		envp->var[i] = var[i++];
	envp->var[i] = 0;
	envp->name = malloc(sizeof(ft_equal_sign(var, 0) + 1));
	if (!envp->name)
		return (ft_free_envp_struct(&envp, -1));	//error
	envp->value = malloc(sizeof(ft_equal_sign(var, 1) + 1));
	if (!envp->value)
		return (ft_free_envp_struct(&envp, -1));	//error
	ft_envp_var_name_and_value(envp);
	envp->prev = NULL;
	envp->next = NULL;
	return (envp);
}
