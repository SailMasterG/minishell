/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 12:47:32 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/19 13:26:45 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/include.h"
#include "signal.h"

void	sigquit_handler(int signal, t_shell *shell)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	shell->exit_status = signal;
	rl_redisplay();
}

void	sigint_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	set_signal_mode(t_signal_modes mode)
{
	struct sigaction	sa;

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
}
