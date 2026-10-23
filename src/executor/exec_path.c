/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 16:07:02 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/22 16:07:21 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**extract_paths(char **envp)
{
	int		i;
	char	**paths_env;

	paths_env = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths_env = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (!paths_env)
		return (NULL);
	return (paths_env);
}

char	*find_cmd(char *cmd, char **paths_env)
{
	char	*path;
	char	*tmp;
	int		i;

	if (!cmd || !paths_env)
		return (NULL);
	i = 0;
	while (paths_env[i] != NULL)
	{
		tmp = ft_strjoin(paths_env[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	resolve_all_paths(t_cmd *cmd, char **envp)
{
	t_cmd	*current;
	char	**envp_routes;

	envp_routes = extract_paths(envp);
	current = cmd;
	while (current != NULL)
	{
		if (current->cmd_args[0] == NULL)
		{
			current->path = NULL;
			current = current->next;
			continue ;
		}
		if (current->cmd_args[0][0] == '/'
			|| ft_strchr(current->cmd_args[0], '/'))
			current->path = ft_strdup(current->cmd_args[0]);
		else
			current->path = find_cmd(current->cmd_args[0], envp_routes);
		current = current->next;
	}
	free_paths(envp_routes);
}
