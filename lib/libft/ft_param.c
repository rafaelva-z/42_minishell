/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:22 by fda-estr          #+#    #+#             */
/*   Updated: 2023/09/20 19:15:32 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_param(va_list *arg, char type, int *len)
{
	if (type == 'c')
		ft_putchar(va_arg(*arg, int), len);
	if (type == '%')
		ft_putchar('%', len);
	if (type == 's')
		ft_putstr(va_arg(*arg, char *), len);
	if (type == 'd' || type == 'i')
		ft_putnbr(va_arg(*arg, int), len);
	if (type == 'u')
		ft_putunsigned(va_arg(*arg, unsigned int), len);
	if (type == 'x')
		ft_putnbrhexa(va_arg(*arg, unsigned int), len, 87);
	if (type == 'X')
		ft_putnbrhexa(va_arg(*arg, unsigned int), len, 55);
	if (type == 'p')
		ft_adress(va_arg(*arg, unsigned long int), len);
}
