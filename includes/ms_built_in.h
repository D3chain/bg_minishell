/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_built_in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garivoir <garivoir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 12:08:20 by garivoir          #+#    #+#             */
/*   Updated: 2025/09/23 12:11:40 by garivoir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILT_IN_H
# define MS_BUILT_IN_H

# include "ms_env.h"

int	ms_cd(char **cmd, t_env *envp);
int	ms_env(char **cmd, t_env *envp);
int	ms_pwd(char **cmd, t_env *envp);
int	ms_echo(char **cmd, t_env *envp);
int	ms_unset(char **cmd, t_env *envp);
int	ms_export(char **cmd, t_env *envp);

#endif