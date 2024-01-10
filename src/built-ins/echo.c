/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/10 19:35:06 by rvaz             ###   ########.fr       */
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
	int	token_nbr;

	nl = 0;
	i = -1;
	token_nbr = 0;
	if (!prompt || !*prompt)
	{
		printf("\n");
		return;
	}
	while (prompt[token_nbr])
		token_nbr++;
	while (prompt[++i] && is_flag(prompt[i]) == 0)
		nl = 1;
	if (is_flag(prompt[i]) == 0)
		return ;
	while (i < token_nbr - 1)
		ft_printf("%s ", prompt[i++]);
	if (i == token_nbr - 1)
		ft_printf("%s", prompt[i]);
	if (nl == 0)
		printf("\n");
}
