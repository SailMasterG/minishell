/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 17:27:36 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/26 17:40:54 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/include.h"

bool	is_name_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (false);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	add_to_env(t_shell *shell, char *name, char *value)
{
	char	**new_env;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (shell->env[++i])
		new_env[i] = shell->env[i];
	if (!value)
		new_env[i] = ft_strdup(name);
	else
	{
		new_env[i] = ft_strjoin(name, "=");
		new_env[i] = ft_strapnd(new_env[i], value);
	}
	i++;
	new_env[i] = NULL;
	free(shell->env);
	shell->env = new_env;
}

char	*get_value(char *arg)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	if (arg[i] == '\0')
		return (NULL);
	i++;
	j = i;
	while (arg[j])
		j++;
	value = malloc(sizeof(char) * (j - i) + 1);
	if (!value)
		return (NULL);
	j = 0;
	while (arg[i])
	{
		value[j] = arg[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return (value);
}

char	*get_name(char *arg)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	while (arg[j] != '=' && arg[j])
	{
		name[j] = arg[j];
		j++;
	}
	name[j] = '\0';
	return (name);
}

void	modify_env(t_shell *shell, int index, char *value)
{
	char	*name;
	char	*new_var;

	name = get_name(shell->env[index]);
	new_var = ft_strapnd(name, "=");
	new_var = ft_strapnd(new_var, value);
	free(shell->env[index]);
	shell->env[index] = new_var;
}
