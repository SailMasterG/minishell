/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:47:32 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/20 02:27:38 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"
#include <signal.h>

volatile sig_atomic_t	g_signal = 0;
/*
void	sigquit_handler(int signal, t_shell *shell)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	shell->exit_status = signal + 128;
	rl_redisplay();
}*/

void	sigint_handler(int signal)
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

void	set_signal_mode(t_signal_modes mode)
{
	struct sigaction	sa;

	rl_done = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (mode == INTERACTIVE)
	{
		sa.sa_handler = sigint_handler;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
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
		sa.sa_handler = sigint_heredoc;
		sa.sa_flags = 0;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}
