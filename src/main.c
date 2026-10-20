/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:06:14 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/19 13:28:31 by rpinheir         ###   ########.ch       */
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
		set_signal_mode(INTERACTIVE);
		g_signal = 0;
		line = readline("Minishell: ");
		if (g_signal == SIGINT)
			shell->exit_status = SIGINT + 128;
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		else if (line[0])
		{
			add_history(line);
			if (shell->cmds)
				free_cmds(shell->cmds);
			shell->cmds = parse(line, shell);
			if (!shell->cmds)
			{
				free(line);
				continue ;
			}
			if (executor(shell))
			free(line);
		}
	}
	free(line);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (1);
	shell.pids = NULL;
	shell.print_newline = true;
	shell.env = enver(env);
	shell.cmds = NULL;
	shell.exit_status = 0;
	show_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	ft_strfree(shell.env);
	return (0);
}
