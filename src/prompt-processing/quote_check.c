/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:52:10 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/11 19:48:46 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 *	@brief checks if there are any quotations left unclosed
 *	@return (0) no quotes left open, (1) open single quote, (2) open double quote
*/
int	quote_check(const char *str)
{
	char	c;

	c = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (!c)
		{
			if (*str == SQUOTE || *str == DQUOTE)
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	return ((c == SQUOTE) + ((c == DQUOTE) * 2));
}
