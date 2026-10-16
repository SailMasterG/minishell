/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 22:11:11 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 22:11:24 by chguerre         ###   ########.ch       */
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
void	redirs_cmd(t_redir *node);
void	childs_exit(t_shell *shell, int i, int *fd, int code);




#endif // !EXEC_H
