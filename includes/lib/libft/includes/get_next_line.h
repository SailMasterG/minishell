/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:35:12 by chguerre          #+#    #+#             */
/*   Updated: 2026/03/04 16:58:47 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "libft.h"

char	*get_next_line(int fd);
char	*read_doc(int fd, char *buff_base);
char	*extract_line(char *buff_base);
char	*append_buff(char *buff_base, char *read_buff);
char	*remainig_buff(char *buff_base);
#endif
