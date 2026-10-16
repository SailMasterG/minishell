/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourlogin <youremail@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 17:52:26 by yourlogin         #+#    #+#             */
/*   Updated: 2026/10/16 17:52:26 by yourlogin        ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

int	executor(t_shell *shell);
int	heredoc_resolve(t_cmd *cmd, int nb_cmd, int pid);


#endif // !EXEC_H
