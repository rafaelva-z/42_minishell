/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_deleter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:04:04 by fda-estr          #+#    #+#             */
/*   Updated: 2023/11/21 19:10:38 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	matrix_deleter(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		if (mtx[i])
			free (mtx[i]);
		mtx[i] = NULL;
		i++;
	}
	free (mtx[i]);
	mtx[i] = NULL;
	free (mtx);
	mtx = NULL;
}
