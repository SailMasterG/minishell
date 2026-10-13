/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 05:40:16 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/21 05:40:21 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	create_cmd(t_cmd *cmd, t_redir *redir, char **arg, char *path, t_cmd *cmd_next)
{
	t_cmd *comands;

	comands = cmd;
	comands->args = arg;
	comands->redir = redir;
	comands->path = path;
	comands->next = cmd_next;
	
}
void	create_redir(t_redir *redir, char *path, t_redir *next_redir, int type)
{
	redir->target = path;
	redir->type = type;
	redir->next = next_redir;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;
	t_redir	redir1;
	int		code;

	(void)argc;
	if (argv[1] && argv[1][0] == '1')
	{
		create_cmd(&cmd1, NULL, (char *[]){"ls", "-l", NULL},
			"/usr/bin/ls", NULL);
		code = executor(&cmd1, envp);
	}
	else if (argv[1] && argv[1][0] == '3')
	{
		create_redir(&redir1, ft_strdup("FIN"), NULL, REDIR_HEREDOC);
		create_cmd(&cmd1, &redir1, (char *[]){"cat", NULL},
			"/usr/bin/cat", &cmd2);
		create_cmd(&cmd2, NULL, (char *[]){"grep", "h", NULL},
			"/usr/bin/grep", &cmd3);
		create_cmd(&cmd3, NULL, (char *[]){"wc", "-l", NULL},
			"/usr/bin/wc", NULL);
		code = executor(&cmd1, envp);
	}
	else if (argv[1] && argv[1][0] == '2')
	{
		create_cmd(&cmd1, NULL,
			(char *[]){"sh", "-c", "kill -SEGV $$", NULL},
			"/bin/sh", NULL);
		code = executor(&cmd1, envp);
	}
	else
		return (write(2, "uso: ./executor 1|3\n", 20), 1);
	return (code);
}
/*
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_redir	redir1;
	t_redir redir2;
	int code;
	char *delimit;

	
	delimit = ft_strdup("FIN");
	create_redir(&redir1, delimit, NULL, REDIR_HEREDOC);
	create_redir(&redir2, "salida.txt", NULL, REDIR_OUT);

	create_cmd(&cmd1, &redir1, (char*[]){"cat",NULL}, "/usr/bin/cat", &cmd2);
	create_cmd(&cmd2, &redir2, (char*[]){"grep","h",NULL}, "/usr/bin/grep", NULL);
	code = executor(&cmd1, envp);
	return (code);
}*/