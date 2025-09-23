/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:01:47 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 11:47:16 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------*/
/* pwd built-in					*/
/*------------------------------*/

#include "minishell.h"

/*------------------------------*/
/* minishell pwd				*/
/* built-in main function		*/
/*------------------------------*/
int	ms_pwd(char **cmd, t_env *envp)
{
	char	*buf;

	(void)envp;
	if (!cmd || !cmd[0])
		return (-1);	//error
	if (ft_strcmp(cmd[0], "pwd") != 0)
		return (-1);	//error
	buf = NULL;
	buf = getcwd(buf, 4096);
	if (!buf)
		return (-1);	//error
	printf("%s\n", buf);
	free(buf);
	return (0);
}
