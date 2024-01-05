/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:30:22 by fda-estr          #+#    #+#             */
/*   Updated: 2023/10/15 20:52:16 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cleaner(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	content[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*save;
	int			toread;

	toread = 0;
	if (fd < 0 || !BUFFER_SIZE || fd > FOPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_cleaner(content[fd]));
	if (!*content[fd])
		toread = read(fd, content[fd], BUFFER_SIZE);
	else
	{
		while (content[fd][toread])
			toread++;
	}
	if (toread < 0)
		return (NULL);
	if (toread < BUFFER_SIZE && toread > 0)
		content[fd][toread] = 0;
	if (!*content[fd])
		return (NULL);
	save = stringbuilder(content[fd], toread, fd);
	return (splitter(save));
}
