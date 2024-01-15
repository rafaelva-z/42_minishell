/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:32:28 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/14 21:09:20 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expansion_prep(char **prompt, int i, int neg_len)
{
	char	*prod;

	if (!prompt || !*prompt || !**prompt)
		return ;
	while ((*prompt)[++i + 1])
	{
		if ((*prompt)[i] == '$' && ft_isdigit((*prompt)[i + 1]))
		{
			(*prompt)[i] = -1;
			(*prompt)[i + 1] = -1;
			neg_len += 2;
		}
	}
	prod = malloc(ft_strlen(*prompt) - neg_len + 1);
	i = -1;
	neg_len = 0;
	while ((*prompt)[++i])
	{
		prod[i - neg_len] = (*prompt)[i];
		if ((*prompt)[i] == -1)
			neg_len++;
	}
	prod[i - neg_len] = 0;
	free (*prompt);
	*prompt = prod;
}

int	expansion_check(char *c, char *prompt, int i)
{
	if ((*c) != '$' || is_inside_quotes(prompt, i) == 1)
		return (1);
	if (ft_isalpha(*(++c)) || *c == '_' || *c == '?')
		return (0);
	return (1);
}

int	expander_aux(char *prompt, int rec, int i)
{
	if (!prompt[i])
	{
		if (rec == 0)
			free(prompt);
		return (1);
	}
	return (0);
}
