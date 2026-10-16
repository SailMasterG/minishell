/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 05:43:32 by chguerr           #+#    #+#             */
/*   Updated: 2026/10/14 15:46:13 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/include.h"

static int	count_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		count;

	count = 0;
	current = cmd;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}

int	wait_pid(pid_t *pid, int nb_cmd)
{
	int		status;
	int		i;
	int		code;
	pid_t	caugth_pid;
	pid_t	last_pid;

	last_pid = pid[nb_cmd - 1];
	i = 0;
	while (i < nb_cmd)
	{
		caugth_pid = waitpid(pid[i], &status, 0);
		if (caugth_pid == last_pid)
		{
			if (WIFSIGNALED(status))
				code = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				code = WEXITSTATUS(status);
		}
		i++;
	}
	return (code);
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
	{
		ft_printf("Error: PATH not found in environment variables.\n");
		return (NULL);
	}
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
		if (current->cmd_args[0][0] == '/'
			|| ft_strchr(current->cmd_args[0], '/'))
			current->path = current->cmd_args[0];
		else
			current->path = find_cmd(current->cmd_args[0], envp_routes);
		current = current->next;
	}
	free(envp_routes);
}

int	executor(t_shell *shell)
{
	int		nbr_cmd;
	int		fd[2];
	pid_t	*pid;
	int		prev_fd;
	int		i;
	t_cmd	*current;
	t_redir	*node;
	int		fd_redir;
	int		code;

	code = 0;
	i = 0;
	nbr_cmd = count_cmd(shell->cmds);
	prev_fd = -1;
	current = shell->cmds;
	pid = malloc(sizeof(pid_t) * nbr_cmd);
	if (pid == NULL)
	{
		perror("malloc");
		return (1);
	}
	heredoc_resolve(shell->cmds, nbr_cmd, getpid());
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
		node = current->redirections;
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			free(pid);
			return (1);
		}
		if (pid[i] == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < nbr_cmd - 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			while (node != NULL)
			{
				fd_redir = -1;
				if (node->type == REDIR_IN)
				{
					fd_redir = open(node->file, O_RDONLY);
					if (fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDIN_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_OUT)
				{
					fd_redir = open(node->file,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDOUT_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_APPEND)
				{
					fd_redir = open(node->file,
							O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd_redir < 0)
					{
						perror("Error de lectura de archivo");
						exit(126);
					}
					dup2(fd_redir, STDOUT_FILENO);
					close(fd_redir);
				}
				else if (node->type == REDIR_HEREDOC)
				{
					fd_redir = open(node->file, O_RDONLY);
					if (fd_redir < 0)
					{
						perror("Error de lectura de archivo 2");
						exit(126);
					}
					unlink(node->file);
					free(node->file);
					dup2(fd_redir, STDIN_FILENO);
					close(fd_redir);
				}
				node = node->next;
			}
			if ((execve(current->path, current->cmd_args, shell->env)) == -1)
			{
				perror("Error: ");
				exit(127);
			}
		}
		while (node != NULL)
		{
			if (node->type == REDIR_HEREDOC)
				free(node->file);
			node = node->next;
		}
		if (current->next != NULL)
			current = current->next;
		if (prev_fd != -1)
			close(prev_fd);
		if (i < nbr_cmd - 1)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	code = wait_pid(pid, nbr_cmd);
	free(pid);
	return (code);
}
