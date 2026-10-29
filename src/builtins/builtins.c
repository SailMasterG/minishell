/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:32:50 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 21:15:57 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	run_builtin_parent(t_shell *shell, t_builtin builtin, t_cmd *cmd)
{
	int	saved_out;
	int	saved_in;
	int	code;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_out == -1)
		return (1);
	if (redirs_cmd(cmd->redirections) != 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return (1);
	}
	code = builtin(shell, cmd->cmd_args);
	dup2(saved_out, STDOUT_FILENO);
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	close(saved_out);
	if (shell->is_exitting)
		(close(0), close(1));
	return (code);
}

t_builtin	get_builtin(char *name)
{
	if (name == NULL)
		return (NULL);
	if (ft_strcmp(name, "echo") == 0)
		return (builtin_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (builtin_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (builtin_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (builtin_export);
	if (ft_strcmp(name, "unset") == 0)
		return (builtin_unset);
	if (ft_strcmp(name, "env") == 0)
		return (builtin_env);
	if (ft_strcmp(name, "exit") == 0)
		return (builtin_exit);
	return (NULL);
}
