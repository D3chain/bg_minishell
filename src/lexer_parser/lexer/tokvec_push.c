/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokvec_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 10:26:25 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 12:37:52 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokv_push_tok(t_tokvec *v, const t_tok *t)
{
	t_tok	tmp;

	if (!tokv_reserve(v, v->len + 1))
		return (MS_ERR);
	tmp = *t;
	if (t->lex)
	{
		tmp.lex = ft_strdup(t->lex);
		if (!tmp.lex)
			return (MS_ERR);
	}
	else
		tmp.lex = NULL;
	v->data[v->len++] = tmp;
	return (MS_OK);
}

int	tokv_add_eof(t_tokvec *v)
{
	t_tok	tok;
	t_ret	r;

	tok.cat = TKC_EOF;
	tok.kind = T_EOF;
	tok.lex = ft_strdup("EOF");
	return (r = tokv_push_tok(v, &tok), free(tok.lex), r);
}
