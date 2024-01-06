/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/06 22:06:54 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
*	@brief determines if the string s is a flag (-n)
*	@param s the string
*	@return 0 if its a flag and 1 if its NOT a flag
*/
static int	is_flag(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) < 2)
		return (1);
	if (s[i] == '-' && s[i + 1] == 'n')
		i += 2;
	else
		return (1);
	while (s[i] && s[i] == 'n')
		i++;
	if (s[i] == 0)
		return (0);
	return (1);
}

/**
*	@brief display a line of text
*	@param prompt the content to be echoed
*/
void	echo(char **prompt)
{
	int	nl;
	int	i;
	int	tok_nbr;

	nl = 0;
	i = -1;
	tok_nbr = 0;
	while (prompt[tok_nbr])
		tok_nbr++;
	while (prompt[++i] && is_flag(prompt[i]) == 0)
		nl = 1;
	if (is_flag(prompt[i]) == 0)
		return ;
	while (i < tok_nbr - 1)
	{
		ft_printf("%s ", prompt[i]);
		i++;
	}
	if (i == tok_nbr - 1)
		ft_printf("%s", prompt[i]);
	if (nl == 0)
		printf("\n");
}
