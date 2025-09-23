/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:34 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:45:55 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* echo built-in					*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* Check the "-n"				*/
/* echo option(s)				*/
/*------------------------------*/
static int	ms_echo_check_opt(char *opt)
{
	int	i;

	if (!opt)
		return (-1);		//error
	if (opt[0] != '-')
		return (-1);		//error
	i = 1;
	if (!opt[i])
		return (-1);		//error
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (-1);	//error
		i++;
	}
	return (0);
}

/*------------------------------*/
/* minishell echo				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_echo(char **cmd, t_env *envp)
{
	int	i;
	int	opt;

	(void)envp;
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "echo") != 0)
		return (-1);	//error
	i = 1;
	opt = 1;
	if (cmd[i] && ms_echo_check_opt(cmd[1]) == 0)
		opt = 0;
	while (cmd[i] && ms_echo_check_opt(cmd[i]) == 0)
		i++;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (opt == 1)
		printf("\n");
	return (0);
}
