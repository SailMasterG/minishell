/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 21:14:13 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/29 17:14:03 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

char	*search_paths(char **envp, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	set_env(char **envp, char *cwd, char *key)
{
	int	pos;

	pos = 0;
	pos = env_pos(envp, key);
	if (pos == -1)
		return (0);
	free(envp[pos]);
	envp[pos] = ft_strjoin(key, cwd);
	return (1);
}

static int	change_dir(t_shell *shell, char *path)
{
	char	*cwd;
	char	**envp;

	envp = shell->env;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	if (set_env(envp, cwd, "PWD="))
		return (1);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(shell->cmds->cmd_args[1]);
		return (free(cwd), 1);
	}
	if (set_env(envp, cwd, "OLDPWD="))
		return (1);
	free(cwd);
	return (0);
}

int	builtin_cd(t_shell *shell, char **cmd_args)
{
	char	*path;

	if (cmd_args[1] && cmd_args[2])
	{
		ft_putendl_fd("too many arguments", 2);
		return (2);
	}
	if (cmd_args[1] == NULL)
	{
		path = search_paths(shell->env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		if (chdir(path) == -1)
		{
			perror("Error");
			return (1);
		}
		return (0);
	}
	else
		path = cmd_args[1];
	return (change_dir(shell, path));
}
