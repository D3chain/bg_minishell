
#include "minishell.h"

typedef enum e_q
{
	Q_NONE,
	Q_SGL,
	Q_DBL
}	t_q;

typedef enum e_s
{
	UC_NONE,
	UC_QUOTE,
	UC_PIPE
}	t_s;

int	is_quote_in_str(char *s)
{
	while (*s)
	{
		if (*s == '\"' || *s == '\'')
			return (1);
		s++;
	}
	return (0);
}

static int	is_quote_closed(const char *s, t_q q, int *st)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (q != Q_DBL && s[i] == '\'')
		{
			if (q == Q_NONE)
				q = Q_SGL;
			else
				q = Q_NONE;
		}
		else if (q != Q_SGL && s[i] == '\"')
		{
			if (q == Q_NONE)
				q = Q_DBL;
			else
				q = Q_NONE;
		}
		i++;
	}
	if (q != Q_NONE)
		return (*st = UC_QUOTE, 0);
	return (1);
}

static int	is_pipe_followed(const char *s, int *st)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (s[i])
	{
		if (s[i] == '|')
			p = 1;
		else if (p && !is_blank(s[i]) && s[i] != '|')
			p = 0;
		i++;
	}
	if (p == 1)
		return (*st = UC_PIPE, 0);
	return (1);
}

int	handle_quote_pipe_unclosed(t_ms *ms)
{
	int		st;

	st = UC_NONE;
	while (!is_quote_closed(ms->line, Q_NONE, &st)
		|| !is_pipe_followed(ms->line, &st))
	{
		if (st == UC_QUOTE)
			ms->line = join_and_free(ms->line, "\n", 1);
		if (!ms->line)
			return (1);
		else if (st == UC_PIPE)
			ms->line = join_and_free(ms->line, " ", 1);
		if (!ms->line)
			return (1);
		ms->line = join_and_free(ms->line, readline("> "), 3);
		add_history(ms->line);
	}
	return (0);
}