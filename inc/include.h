/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:18:12 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/19 13:24:41 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDE_H
# define INCLUDE_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>

# include "struct.h"
# include "enum.h"
# include "parse.h"
# include "exec.h"

extern volatile sig_atomic_t	g_signal;
void	set_signal_mode(t_signal_modes mode);
#endif
