/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:47:32 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/20 22:26:44 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include "../inc/include.h"
#include <signal.h>

volatile sig_atomic_t	g_signal = 0;

void	sigint_handler(int signal) // CTRL+C
{
	g_signal = signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_heredoc(int signal)
{
	g_signal = signal;
	rl_done = 1;
}

static void set_mode_interactive(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}
static void set_mode_heredoc(struct sigaction *sa)
{
	sa->sa_handler = sigint_heredoc;
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}
void	set_signal_mode(t_signal_modes mode)
{
	struct sigaction	sa;

	rl_done = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (mode == INTERACTIVE)
	{
		set_mode_interactive(&sa);
	}
	else if (mode == EXECUTION)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == FORKED)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == HEREDOC)
	{
		set_mode_heredoc(&sa);
	}
}
