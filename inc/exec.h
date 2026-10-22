/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:11:11 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/22 20:24:11 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

int		executor(t_shell *shell);
int		exec_heredoc(t_cmd *cmd, int nb_cmd, int pid);
int		count_cmd(t_cmd *cmd);
void	resolve_all_paths(t_cmd *cmd, char **envp);
char	*find_cmd(char *cmd, char **paths_env);
char	**extract_paths(char **envp);
int		redirs_cmd(t_redir *node);
void	childs_exit(t_shell *shell, int i, int *fd, int code);
int		fork_setup(t_shell *shell, int i, int *fd, t_cmd *current);
int		wait_pid(pid_t *pid, int nb_cmd);
void	setup_child_pipes(t_shell *shell, int i, int *fd);
int		pipe_creator(t_shell *shell, int i, int *fd, pid_t *pid);
void	erase_before_files(t_cmd *cmd, t_redir *limit);
#endif // !EXEC_H
