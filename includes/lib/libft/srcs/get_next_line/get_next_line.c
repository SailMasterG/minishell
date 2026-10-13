/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 22:35:29 by chguerre          #+#    #+#             */
/*   Updated: 2026/02/20 00:00:02 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_freemem(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (*ptr);
}

char	*get_next_line(int fd)
{
	static char	*buff_base[1080];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff_base[fd])
	{
		buff_base[fd] = malloc(1 * sizeof(char));
		if (!buff_base[fd])
			return (NULL);
		buff_base[fd][0] = '\0';
	}
	if (!ft_strchr(buff_base[fd], '\n'))
		buff_base[fd] = read_doc(fd, buff_base[fd]);
	if (!buff_base[fd] || buff_base[fd][0] == '\0')
		return (ft_freemem(&buff_base[fd]));
	line = extract_line(buff_base[fd]);
	if (!line)
		return (ft_freemem(&buff_base[fd]));
	buff_base[fd] = remainig_buff(buff_base[fd]);
	return (line);
}

char	*read_doc(int fd, char *buff_base)
{
	char	*new_buff;
	int		r;
	int		len;

	r = 1;
	while (r > 0)
	{
		len = ft_strlen(buff_base);
		new_buff = (char *)malloc(len + BUFFER_SIZE + 1);
		if (!new_buff)
			return (ft_freemem(&buff_base));
		ft_strlcpy(new_buff, buff_base, len + 1);
		r = read(fd, new_buff + len, BUFFER_SIZE);
		if (r == -1)
		{
			free(new_buff);
			return (ft_freemem(&buff_base));
		}
		new_buff[len + r] = '\0';
		free(buff_base);
		buff_base = new_buff;
		if (ft_strchr(new_buff, '\n'))
			break ;
	}
	return (buff_base);
}

/*
char	*read_doc(int fd, char *buff_base)
{
	char	*new_buff;
	int		r_read;
	char	*read_buff;
	int		len;

	r_read = 1;
	read_buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!read_buff)
		return (ft_freemem(&buff_base));
	while (buff_base && r_read > 0)
	while (r_read > 0)
	{
		r_read = read(fd, read_buff, BUFFER_SIZE);
		len = ft_strlen(buff_base);
		new_buff = (char *)malloc(len + BUFFER_SIZE + 1);
		if (!new_buff)
			return (ft_freemem(&buff_base));
		ft_strlcpy(new_buff, buff_base, len + 1);
		r_read = read(fd, new_buff + len, BUFFER_SIZE);
		if (r_read == -1)
		{
			free(read_buff);
			free(new_buff);
			return (ft_freemem(&buff_base));
		}
		if (r_read == 0)
		new_buff[len + r_read] = '\0';
		free(buff_base);
		buff_base = new_buff;
		if (ft_strchr(buff_base + len, '\n'))
			break ;
		read_buff[r_read] = '\0';
		buff_base = append_buff(buff_base, read_buff);
		if (ft_strchr(read_buff, '\n'))
			break ;
	}
	free(read_buff);
	return (buff_base);
}

char	*append_buff(char *buff_base, char *read_buff)
{
	char	*temp;

	temp = ft_strjoin(buff_base, read_buff);
	free(buff_base);
	return (temp);
}
*/
char	*extract_line(char *buff_base)
{
	char	*pos;
	char	*line;
	size_t	len;

	if (buff_base == NULL)
		return (NULL);
	pos = ft_strchr(buff_base, '\n');
	if (pos != NULL)
		len = (pos - buff_base) + 1;
	else
		len = ft_strlen(buff_base);
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buff_base, len + 1);
	return (line);
}
