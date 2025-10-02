/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:55:12 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 11:22:18 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "libft.h"
# include "ms_types.h"
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

# define MS_BUF_ERR_SIZE	256

typedef enum	e_ret
{
	MS_OK		= 0,
	MS_ERR		= 1,
	MS_MISUSE	= 2,
	MS_EOF		= 3,
	MS_NOTEXEC	= 126,
	MS_NOTFOUND	= 127,
	MS_SIGINT	= 130,
	MS_SIGQUIT	= 131,
	MS_EXIT_NAN	= 255
}	t_ret;

int		fill1(char *buf, const char *a);
int		fill2(char *buf, const char *a, const char *b);
int		fill3(char *buf, const char *a, const char *b, const char *c);

int		ms_err(int code, const char *ctx, const char *msg);
int		ms_perror(int code, const char *ctx);
int		ms_syntax_err(const char *tok);
int		ms_cmd_err(int code, const char *cmd);
int		ms_builtin_err(int code, const char *bi, const char *detail);

void	ms_fatal(t_ms *ms, const char *ctx);

#endif