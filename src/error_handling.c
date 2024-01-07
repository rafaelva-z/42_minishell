/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:05:22 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/07 17:05:14 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	(6, "ola", "cuntao", ...)

char	*message_joiner(int nbr, ...)
{
	va_list arg;
	int		i;
	char	*str;

	str = ft_strdup("");
	i = -1;
	va_start(arg, nbr);
	while (++i < nbr)
		str = ft_strjoin_free(str, va_arg(arg, char *), 1);
	va_end(arg);
	return (str);	
}
