/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:38:26 by fda-estr          #+#    #+#             */
/*   Updated: 2023/09/20 19:24:58 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nlcheck(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*splitter(char *save)
{
	int		i;
	char	*prod;

	i = 0;
	while (save[i] != '\n' && save[i])
		i++;
	if (save[i] == '\n')
	{
		prod = malloc(i + 2);
		prod[i] = '\n';
		i++;
	}
	else
		prod = malloc(i + 1);
	prod[i] = '\0';
	i = 0;
	while (save[i] != '\n' && save[i])
	{
		prod[i] = save[i];
		i++;
	}
	if (save)
		free (save);
	return (prod);
}

char	*ft_strjoin_gnl(char *dest, char *src, int toread)
{
	char	*prod;
	int		i;
	int		j;

	i = 0;
	while (dest && dest[i])
		i++;
	prod = malloc(i + toread + 1);
	if (!prod)
		return (NULL);
	i = -1;
	j = -1;
	while (dest && dest[++i])
		prod[i] = dest[i];
	while (src && src[++j] && j < toread)
		prod[i + j] = src[j];
	prod[i + j] = 0;
	if (dest)
		free (dest);
	return (prod);
}

void	saver(char *content, char *save)
{
	int	i;
	int	j;

	i = 0;
	while (save && save[i])
		i++;
	if (i == 1)
	{
		*content = 0;
		return ;
	}
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		*content = 0;
		return ;
	}
	i++;
	j = -1;
	while (save[++j + i])
		content[j] = save [j + i];
	content[j] = 0;
}

char	*stringbuilder(char *content, int toread, int fd)
{
	char	*train;
	int		i;

	i = -1;
	train = malloc(toread + 1);
	if (train == 0)
		return (NULL);
	while (content[++i])
		train[i] = content[i];
	train[i] = 0;
	while (toread > 0 && nlcheck(train) == 0)
	{
		toread = read(fd, content, BUFFER_SIZE);
		if (toread > 0)
			train = ft_strjoin_gnl(train, content, toread);
	}
	saver(content, train);
	return (train);
}
