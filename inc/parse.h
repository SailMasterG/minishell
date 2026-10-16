/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinheir <rpinheir@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:16:25 by rpinheir          #+#    #+#             */
/*   Updated: 2026/10/16 14:19:28 by rpinheir         ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"
# include "enum.h"

t_cmd			*parse(char *line, t_shell *shell);
t_cmd			*build_cmds(t_token *tokens);
t_token			*lexer(char *line);
t_token			*new_token(t_token_type token_type, char *value);
t_redir_type	token_to_redir_type(t_token_type token_type);
void			add_token(t_token **head, t_token **last, t_token *new_token);
void			free_tokens(t_token *tokens);
void			handle_operator(char *line, int *i, t_token **head,
					t_token **last);
void			append_redir(t_redir **head, t_redir_type type, char *file);
void			free_cmds(t_cmd *cmds);
void			fill_fields(char *value, char **cmd_args, int *i);
char			*strip_quotes(char *string);
char			*resolve_redir_file(t_redir_type type,
					char *file, bool *is_quoted);
char			**enver(char **environ);
char			*value_expand(char *value, int *i, t_shell *shell);
bool			expansion(t_token *head, t_shell *shell);
bool			validation(t_token *head);
bool			is_redir(t_token *tokens);
void			mark_range(char *s);
int				count_fields(char *value);

void			debug_cmds(t_cmd *cmds);
void			debug_redirs(t_cmd *cmd, int fd);
void			debug_tokens(t_token *tokens, char *line);

#endif // !PARSE_H
