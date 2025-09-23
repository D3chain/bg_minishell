/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:38 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:03:32 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* cd built-in					*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Finding HOME path			*/
/* from envp main variable		*/
/*------------------------------*/
static char	*ms_cd_home_path(t_envp *envp)
{
	char	*home;
	t_envp	*envp_temp;

	if (!envp)
		return (NULL);
	envp_temp = envp;
	while (envp_temp)
	{
		if (ft_strncmp(envp_temp->var, "HOME=", 5) == 0)
		{
			home = ft_strdup(&envp_temp->var[5]);
			if (!home)
				return (NULL);	//error
			return (home);
		}
		envp_temp = envp_temp->next;
	}
	return (NULL);
}

/*------------------------------*/
/* minishell cd					*/
/* built-in main function		*/
/*------------------------------*/
int	ms_cd(char **cmd, t_envp *envp)
{
	int		cd;
	char	*home;

	if (!cmd || !cmd[0])
		return (-1);		//error
	if (cmd[0] && cmd[1] && cmd[2])
		return (-1);		//error
	if (!envp)
		return (-1);		//error
	if (ft_strcmp(cmd[0], "cd") != 0)
		return (-1);		//error
	if (!cmd[1])
	{
		home = ms_cd_home_path(envp);
		if (!home)
			return (-1);	//error
		cd = chdir(home);
		free(home);
		return (cd);
	}
	cd = chdir(cmd[1]);
	return (cd);
}
