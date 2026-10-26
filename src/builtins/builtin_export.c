/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:13:58 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/26 18:10:32 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

void	display_export(char **env)
{
	int		i;
	char	*eq;

	i = 0;
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		ft_putstr_fd("declare -x ", 1);
		if (!eq)
			ft_putendl_fd(env[i], 1);
		else
		{
			write(1, env[i], eq - env[i] + 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(eq + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		i++;
	}
}

void	export_dup(t_shell *shell)
{
	int		n;
	int		i;
	char	**tmp_env;

	n = 0;
	i = 0;
	while (shell->env[n])
		n++;
	tmp_env = malloc(sizeof(char *) * (n + 1));
	if (!tmp_env)
		return ;
	while (shell->env[i])
	{
		tmp_env[i] = shell->env[i];
		i++;
	}
	tmp_env[i] = NULL;
	sort_env(tmp_env);
	free(tmp_env);
}

static int	export_one(t_shell *shell, char *arg)
{
	char	*name;
	char	*value;
	int		env_indx;

	if (!is_name_valid(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	name = get_name(arg);
	value = get_value(arg);
	env_indx = env_pos(shell->env, name);
	if (env_indx != -1)
	{
		if (value)
			modify_env(shell, env_indx, value);
	}
	else
		add_to_env(shell, name, value);
	free(name);
	free(value);
	return (0);
}

int	builtin_export(t_shell *shell, char **cmd_args)
{
	int		i;
	char	*arg;
	bool	invalid;

	i = 0;
	invalid = false;
	if (!cmd_args[1])
	{
		export_dup(shell);
		return (0);
	}
	while (cmd_args[++i])
	{
		arg = cmd_args[i];
		if (export_one(shell, arg))
			invalid = true;
	}
	return (invalid);
}
