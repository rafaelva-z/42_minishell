/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:05:22 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/12 20:54:42 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	display_error(char *error_msg, int exit_status)
{
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	return (exit_status);
}
