/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+		  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:06:14 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/22 16:19:18 by rpinheir         ###   ########.ch       */
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

int	entry_exec(char *line, t_shell *shell)
{
	add_history(line);
	if (shell->cmds)
		free_cmds(shell->cmds);
	shell->cmds = parse(line, shell);
	if (!shell->cmds)
		return (free(line), 1);
	executor(shell);
	free(line);
	return (0);
}

void	show_prompt(t_shell *shell)
{
	char	*line;

	while (!shell->is_exitting)
	{
		set_signal_mode(INTERACTIVE);
		line = readline("Minishell: ");
		if (g_signal == SIGINT)
			shell->exit_status = SIGINT + 128;
		g_signal = 0;
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
		else if (line[0] && entry_exec(line, shell) == 1)
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	if (ac > 1 && av[0])
		return (1);
	shell.is_exitting = false;
	shell.pids = NULL;
	shell.print_newline = true;
	shell.env = enver(env);
	shell.cmds = NULL;
	shell.exit_status = 0;
	show_prompt(&shell);
	if (shell.cmds)
		free_cmds(shell.cmds);
	ft_strfree(shell.env);
	return (shell.exit_status);
}
