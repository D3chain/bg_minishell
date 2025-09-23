/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:06:37 by echatela          #+#    #+#             */
/*   Updated: 2025/09/23 10:48:26 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_error.h"

int	ms_err(int code, const char *ctx, const char *msg)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	if (ft_strlen(ctx) + ft_strlen(msg) + 16 > MS_BUF_ERR_SIZE -1)
		write(2, "miniprout: pipi popo\n", 22);
	i = 0;
	ft_bzero(err_buf, MS_BUF_ERR_SIZE);
	i += fill2(err_buf, "minishell: ", ctx);
	i += fill2(err_buf + i, ": ", msg);
	i += fill1(err_buf + i, "\n");
	write(2, err_buf, i);
	return (code);
}

int	ms_perror(int code, const char *ctx)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	if (ft_strlen(ctx) + ft_strlen(strerror(errno)) + 14 > MS_BUF_ERR_SIZE -1)
		write(2, "miniprout: pipi popo\n", 22);
	i = 0;
	i += fill2(err_buf, "minishell: ", ctx);
	i += fill3(err_buf + i, ": ", strerror(errno), "\n");
	write(2, err_buf, i);
	return (code);
}

int	ms_syntax_err(const char *tok)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	if (ft_strlen(tok) + 48 > MS_BUF_ERR_SIZE -1)
		write(2, "miniprout: pipi popo\n", 22);
	i = 0;
	i += fill3(err_buf, "minishell: syntax error near unexpected token '", tok, "\n");
	write(2, err_buf, i);
	return (MS_MISUSE);
}

int	ms_cmd_err(int code, const char *cmd)
{
	if (code == MS_NOTFOUND)
		ms_err(code, cmd, "command not found");
	else if (code == MS_NOTEXEC)
		ms_err(code, cmd, "permission denied");
	else
		ms_perror(MS_ERR, cmd);
	return (code);
}

int	ms_builtin_err(int code, const char *bi, const char *detail)
{
	char	err_buf[MS_BUF_ERR_SIZE];
	int		i;

	if (ft_strlen(bi) + ft_strlen(detail) + 14 > MS_BUF_ERR_SIZE -1)
		write(2, "miniprout: pipi popo\n", 22);
	i = 0;
	i += fill3(err_buf, "minishell: ", bi, ": ");
	i += fill2(err_buf + i, detail, "\n");
	return (code);
}
