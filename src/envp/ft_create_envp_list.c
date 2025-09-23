/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_envp_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:32:55 by garivoir          #+#    #+#             */
/*   Updated: 2025/09/19 13:58:29 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* New "envp"					*/
/* list creation file			*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Free "envp" list				*/
/*------------------------------*/
void	ft_clear_lstenvp(t_envp **envp, int status)
{
	t_envp	*temp;

	temp = NULL;
	if (!envp || !*envp)
		return ;
	while (*envp)
	{
		temp = (*envp)->next;
		ft_free_envp_struct(envp, status);
		(*envp) = temp;
	}
	return ;
}

/*------------------------------*/
/* Create a new "envp"			*/
/* variable with a chained list	*/
/*------------------------------*/
t_envp	*ft_create_lstenvp(char **old_envp)
{
	int		i;
	t_envp	*new_envp;
	t_envp	*new_envp_temp;
	t_envp	*new_envp_prev_temp;

	if (!old_envp || !old_envp[0])
		return (NULL);
	new_envp = ft_new_envp(old_envp[0]);
	if (!new_envp)
		return (NULL);
	i = 1;
	new_envp_temp = new_envp;
	while (old_envp[i])
	{
		new_envp_prev_temp = new_envp;
		new_envp->next = ft_new_envp(old_envp[i]);
		if (!new_envp->next)
		{
			ft_clear_lstenvp(&new_envp_temp, -1);	//error
			return (NULL);
		}
		new_envp = new_envp->next;
		new_envp->prev = new_envp_prev_temp;
	}
	return (new_envp_temp);
}
