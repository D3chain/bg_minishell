/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:28:27 by echatela          #+#    #+#             */
/*   Updated: 2025/10/02 10:58:58 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H

# include <signal.h>

typedef enum e_sigmode
{
	SIGMODE_INTERACTIVE,
	SIGMODE_HEREDOC,
	SIGMODE_CHILD
}	t_sigmode;

extern volatile sig_atomic_t g_sigstate;

void init_signals(void);
void child_signals(void);

#endif