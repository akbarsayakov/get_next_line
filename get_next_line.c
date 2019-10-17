/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asayakov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 14:35:54 by asayakov          #+#    #+#             */
/*   Updated: 2019/10/12 14:36:00 by asayakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		save_line(const int fd, char **s, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[fd][i] != '\0' && s[fd][i] != '\n')
		i++;
	if (s[fd][i] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
	}
	else if (s[fd][i] == '\n')
	{
		*line = ft_strsub(s[fd], 0, i);
		tmp = ft_strdup(s[fd] + i + 1);
		ft_strdel(&s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[FD_SIZE];
	int			byte_size;
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || fd > FD_SIZE || !line)
		return (-1);
	if (!s[fd])
		s[fd] = ft_strnew(1);
	while ((byte_size = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[byte_size] = '\0';
		tmp = ft_strjoin(s[fd], buffer);
		ft_strdel(&s[fd]);
		s[fd] = tmp;
		if (ft_strrchr(s[fd], '\n'))
			break ;
	}
	if (byte_size < 0)
		return (-1);
	else if (s[fd][0] == '\0' && !byte_size)
		return (0);
	return (save_line(fd, s, line));
}
