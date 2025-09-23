/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:20:25 by echatela          #+#    #+#             */
/*   Updated: 2025/09/22 09:21:13 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_cwd_in_env(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 3) == 0)
			return (ft_strdup(env->val)); // caller free
		env = env->next;
	}
	return (NULL);
}

static char	*prompt_build(const char *prefix, const char *cwd)
{
	size_t	lp;
	size_t	lc;
	char	*p;

	lp = ft_strlen(prefix);
	lc = ft_strlen(cwd);
	p = (char *)malloc(lp + lc + 3);
	if (!p)
		return (NULL);
	ft_memcpy(p, prefix, lp);
	ft_memcpy(p + lp, cwd, lc);
	p[lp + lc] = '$';
	p[lp + lc + 1] = ' ';
	p[lp + lc + 2] = '\0';
	return (p);
}

t_ret	ms_prompt_make(char **out_prompt, t_env *env)
{
	char	*cwd;

	if (!out_prompt)
		return (MS_ERR);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = find_cwd_in_env(env);
	if (!cwd)
		cwd = ft_strdup("");
	if (!cwd)
		return (MS_ERR);
	*out_prompt = prompt_build("minishell:", cwd);
	free(cwd);
	if (!*out_prompt)
		return (MS_ERR);
	return (MS_OK);
}