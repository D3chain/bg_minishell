/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:00:39 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 12:24:18 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_init(t_ms *ms, int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (1);
	(void)argv;
	ft_bzero(ms, sizeof(t_ms));
	ms->envp = envp;
	ms->tok = NULL;
	return (0);
}

void	print_tok(t_ms ms)
{
	int	i;

	i = 0;
	while (ms.tok)
	{
		printf("node %d:\n    lex: %s\n    cat: %d\n    kind: %d\n    next: %p\n    prev: %p\n\n", i, ms.tok->lex, ms.tok->cat, ms.tok->kind, ms.tok->next, ms.tok->prev);
		i++;
		ms.tok = ms.tok->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;
	
	if (ms_init(&ms, argc, argv, envp) != 0)
		return (1);
	while (1)
	{
		ms.line = ms_term(&ms, envp);
		ms.ast = ms_lexer_parser(&ms, ms.line);
		// ms_parse(&ms);
		// ms_process(&ms);
		ms_cleanup(&ms);
	}
}
