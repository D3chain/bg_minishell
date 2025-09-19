/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_stream.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:16:13 by echatela          #+#    #+#             */
/*   Updated: 2025/09/19 13:18:02 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STREAM_H
# define MS_STREAM_H

# include "ms_types.h"

typedef struct s_stream {
	t_tok	*vec;
	int		len;
	int		i;
}	t_stream;

void	stream_init(t_stream *s, t_tok *v, int len);
t_tok	*stream_peek(t_stream *s);
t_tok	*stream_peekn(t_stream *s, int n);
t_tok	*stream_get(t_stream *s);
int		stream_at_eof(t_stream *s);

#endif