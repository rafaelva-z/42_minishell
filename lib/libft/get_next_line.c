/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 01:12:55 by fda-estr          #+#    #+#             */
/*   Updated: 2023/10/15 20:55:00 by fda-estr         ###   ########.fr       */
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
	static char	content[BUFFER_SIZE + 1];
	char		*save;
	int			toread;

	toread = 0;
	if (fd < 0 || !BUFFER_SIZE || fd > FOPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_cleaner(content));
	if (!*content)
		toread = read(fd, content, BUFFER_SIZE);
	else
	{
		while (content[toread])
			toread++;
	}
	if (toread < 0)
		return (NULL);
	if (toread < BUFFER_SIZE && toread > 0)
		content[toread] = 0;
	if (!*content)
		return (NULL);
	save = stringbuilder(content, toread, fd);
	return (splitter(save));
}
