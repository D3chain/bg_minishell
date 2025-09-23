/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fatal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:50:51 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 13:02:23 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_fatal(t_ms *ms, const char *ctx)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	if (ft_strlen(ctx) + ft_strlen(strerror(errno)) + 14 > MS_BUF_ERR_SIZE -1)
		write(2, "miniprout: pipi popo\n", 22);
	i = 0;
	ft_bzero(err_buf, MS_BUF_ERR_SIZE);
	i += fill2(err_buf, "minishell: ", ctx);
	i += fill3(err_buf + i, ": ", strerror(errno), "\n");
	write(2, err_buf, i);
	ms_cleanup_all(ms);
	exit(1);
}
