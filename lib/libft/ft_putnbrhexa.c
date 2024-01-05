/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:51:11 by fda-estr          #+#    #+#             */
/*   Updated: 2023/09/20 19:25:41 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrhexa(unsigned int nbr, int *len, int lowup)
{
	if (nbr > 15)
	{
		ft_putnbrhexa(nbr / 16, len, lowup);
		ft_putnbrhexa(nbr % 16, len, lowup);
	}
	if (nbr < 16)
	{
		if (nbr > 9)
			ft_putchar(nbr + lowup, len);
		else
			ft_putchar(nbr + 48, len);
	}
}
