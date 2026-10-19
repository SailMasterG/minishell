/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:47:32 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/20 00:39:07 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"
#include <signal.h>

volatile sig_atomic_t	g_signal = 0;

void	sigquit_handler(int signal, t_shell *shell)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	shell->exit_status = signal;
	rl_redisplay();
}

void	sigint_handler(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\n", 1); // we can use write? because this funcition use
	rl_on_new_line();         // 2. Tell to Readline: "we are in newline"
	rl_replace_line("", 0);   // 3. Empty the text that user was write
	rl_redisplay();
}

void	sigint_heredoc(int signal)
{
	g_signal = signal;
	ft_putstr_fd("\n", 1);
	rl_done = 1;
}

void	set_signal_mode(t_signal_modes mode)
{
	struct sigaction	sa;

	rl_done = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
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
