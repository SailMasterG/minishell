/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:13:40 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 21:13:51 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

int	print_err(t_shell *shell, char **args, int i)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[i], 2);
	ft_putendl_fd(": numeric argument required", 2);
	shell->exit_status = 2;
	return (2);
}

void	check_overflow(t_shell *shell, char **args, int i)
{
	long long	exit_number;
	bool		overflow;

	if (args[i])
	{
		exit_number = (unsigned char)ft_atoll(args[1], &overflow);
		if (overflow)
		{
			print_err(shell, args, i);
			shell->exit_status = 2;
		}
		else
			shell->exit_status = exit_number;
	}
}

int	ft_isnumeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, char **cmd_args)
{
	if (cmd_args[1] && !ft_isnumeric(cmd_args[1]))
	{
		if (print_err(shell, cmd_args, 1) == 2)
		{
			shell->is_exitting = true;
			return (2);
		}
	}
	check_overflow(shell, cmd_args, 1);
	if (cmd_args[1] && cmd_args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return (1);
	}
	shell->is_exitting = true;
	return (shell->exit_status);
}
