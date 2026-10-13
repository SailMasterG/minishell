/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 05:43:32 by chguerr           #+#    #+#             */
/*   Updated: 2026/09/21 05:58:11 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc_resolve(t_cmd *cmd, int nb_cmd, int pid)
{
	int fd;
	t_cmd *current;
	t_redir *node;
	char *line;
	char *route_path;
	char *path_temp;
	int i;
	
	current = cmd;
	
	i = 0;
	while(i < nb_cmd)
	{
		node = current->redir;
		while(node != NULL)
		{
			if(node->type == REDIR_HEREDOC)
			{
				char *pid_txt;
				char *id;

				pid_txt = ft_itoa(pid);
				id = ft_itoa(i);
				path_temp = ft_strjoin("/tmp/sailmaster_",pid_txt);
				route_path = ft_strjoin(path_temp, id);
				free(pid_txt);
				free(id);
				free(path_temp);
				fd = open(route_path, O_CREAT | O_WRONLY , 0644);
				if(fd < 0)
				{
					perror("Error de Lectura de archivo 1");
					exit(126);
				}
				while(1)
				{
					line = readline("heredoc>");
					if(line == NULL)
						break;
					if(ft_strncmp(line, node->target, ft_strlen(node->target) + 1) == 0)
						break;
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1  );
					free(line);
				}
				free(line);
				close(fd);
				free(node->target); 
				node->target = route_path;
			}
			node = node->next;
		}
		current = current->next;
		i++;
	}
}

static int count_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;
	
	count = 0;
	current = cmd;
	while(current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

int wait_pid(pid_t *pid, int nb_cmd)
{
	int		status;
	int		i;
	int 	code;
	pid_t	caugth_pid;

	i = 0;
	pid_t last_pid = pid[nb_cmd - 1];
	while(i < nb_cmd)
	{	
		caugth_pid = waitpid(pid[i], &status, 0);
		if(caugth_pid == last_pid)
		{
			if (WIFSIGNALED(status))
				code = WTERMSIG(status) + 128;
			else if (WIFEXITED(status) )
				code = WEXITSTATUS(status);
		}
		i++;
	}
	return (code);
}

int executor(t_cmd *cmd, char **envp)
{
	int nbr_cmd = count_cmd(cmd);
	int fd[2];
	pid_t *pid;

	int prev_fd; 
	int i;
	t_cmd *current;

	t_redir *node;
	int fd_redir;
	int code;
	code = 0;


	i = 0;
	prev_fd = -1;
	current = cmd;
	pid = malloc(sizeof(pid_t)*nbr_cmd);
	if(pid ==NULL)
	{
		perror("malloc");
		return(1);
	}
	heredoc_resolve(cmd, nbr_cmd, getpid());
	while (i < nbr_cmd)
	{
		
		if (i < nbr_cmd - 1)
		{
			if (pipe(fd) == -1)
			{
			perror("pipe");
			free(pid);
			return (1);
			}
		}
		node = current->redir;
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			free(pid);
			return (1);
		}
		if(pid[i] == 0)
		{
			if(prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if(i < nbr_cmd  - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			while(node != NULL)
			{
				fd_redir = -1;
				if(node->type == REDIR_IN)
				{
					fd_redir = open(node->target, O_RDONLY);
					if(fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDIN_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_OUT)
				{
					fd_redir = open(node->target, O_WRONLY | O_CREAT | O_TRUNC , 0644);
					if(fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDOUT_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_APPEND)
				{
					fd_redir = open(node->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if(fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDOUT_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_HEREDOC)
				{
					fd_redir = open(node->target, O_RDONLY);
					if(fd_redir < 0)
					{
						perror("Error de lectura de archivo 2");
						exit(126);
					}
					unlink(node->target);
					free(node->target); 
					dup2(fd_redir, STDIN_FILENO);
					close(fd_redir);
				}
				
				node = node->next;
			}
				execve(current->path, current->args, envp);
				perror("Error: ");
				exit(127);
		}
		while(node != NULL)
		{
			if(node->type == REDIR_HEREDOC)
				free(node->target);
			node = node->next;
		}
		if(current->next != NULL)
			current = current->next;
		if(prev_fd != -1)
			close(prev_fd);
		if(i < nbr_cmd - 1)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	code = wait_pid(pid, nbr_cmd);
	free(pid);
	return(code);
}