/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chr@student.lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 20:01:59 by chguerre          #+#    #+#             */
/*   Updated: 2026/10/16 20:02:51 by chguerre         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

int		executor(t_shell *shell);
int		heredoc_resolve(t_cmd *cmd, int nb_cmd, int pid);
int		count_cmd(t_cmd *cmd);
void	resolve_all_paths(t_cmd *cmd, char **envp);
char	*find_cmd(char *cmd, char **paths_env);
char	**extract_paths(char **envp);
void	redirs_cmd(t_redir *node, t_shell *shell);



#endif // !EXEC_H
