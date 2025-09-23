/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:15 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 15:50:46 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* exit built-in				*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* minishell exit				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_exit(char **cmd, t_envp *envp)
{
	int	i;
	
	(void)cmd;
	(void)envp;
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "unset") != 0)
		return (-1);	//error
	// exit(0);
	return (0);
}
