/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saouissi <saouissi@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:01:33 by rpinheir          #+#    #+#             */
/*   Updated: 2026/07/20 19:40:01 by saouissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/include.h"

char	**enver(char **envp)
{
	int		i;
	char	**env;

	i = -1;
	while (envp[++i])
		;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	while (envp[++i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
			return (ft_strfree(env), NULL);
	}
	env[i] = NULL;
	return (env);
}

void	show_prompt(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell: ");
		if (!line || line[0] == 0)
			break ;
		else if (line[0])
		{
			//if (shell->cmds)
				//free cmds
			printf("in line[0] !");
			shell->cmds = parse(line, shell);
			if (!shell->cmds)
			{
				free(line);
				continue ;
			}
			// executor here
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (1);
	shell.pids = NULL;
	shell.print_newline = true;
	shell.env = enver(env);
	show_prompt(&shell);
	shell.cmds = NULL;
	if (shell.cmds)
		printf("Free cmds");
	return (0);
}
