/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:32:28 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/15 17:16:23 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief removes invalid expantions with numbers like "$123" becomes "23"
*/
void	expansion_prep(char **prompt, int i, int neg_len, char *prod)
{
	if (!prompt || !*prompt || !**prompt)
		return ;
	while ((*prompt)[++i + 1])
	{
		if (is_inside_quotes(*prompt, i) != 1
			&& (*prompt)[i] == '$' && ft_isdigit((*prompt)[i + 1]))
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

/**
 * @brief	checks if the given character '$' is the start of a valid expansion
 * @return	1 if the expansion is not valid, 0 if the expansion is valid
*/
int	expansion_check(char *c, char *prompt, int i)
{
	if ((*c) != '$' || is_inside_quotes(prompt, i) == 1)
		return (1);
	if (ft_isalpha(*(++c)) || *c == '_' || *c == '?')
		return (0);
	return (1);
}

/**
 * @brief checks if there is a valid expansion on the string
 * @return 0 if there is no valid expansion, 1 if there is.
*/
int	expansion_check_str(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i] && (is_inside_quotes(prompt, i) == 1 || prompt[i] != '$'))
		i++;
	if (prompt[i])
		return (1);
	return (0);
}

/**
 * @brief	converts all '$' between SQUOTES to -1
*/
void	expansion_masker(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '$' && (is_inside_quotes(prompt, i) == 1 
				|| (prompt[i + 1] == ' ' || prompt[i + 1] == '\"'
					|| prompt[i + 1] == '\'' || prompt[i + 1] == '\0')))
			prompt[i] = -1;
	}
}
