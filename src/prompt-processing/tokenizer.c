/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 22:30:35 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/13 15:53:15 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
*	@brief Marks all outer quotes for further removal
*	@param token pointer to the token
*	@param the type of quote to be replaced
*	@return the number of caracters inbetween outer quotes
*/
static int	quotes_neutralizer(char *token, char quote)
{
	int	i;

	i = -1;
	token[++i] *= -1;
	while (token[++i])
	{
		if (token[i] == quote)
		{
			token[i] *= -1;
			return (i);
		}
	}
	return (i);
}

/**
*	@brief marks every special character in a prompt
*	@param s the prompt
*/
static void	prompt_neutralizer(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i += quotes_neutralizer(s + i, s[i]);
		if (s[i] == '<' || s[i] == '>' || s[i] == '|' || s[i] == ' ')
			s[i] *= -1;
	}
}

/**
*	@brief Removes all marked quotes
*	@param token pointer to the token
*/
static void	unquoter(char **token)
{
	int		nbr_quotes;
	int		i;
	int		j;
	char	*prod;

	nbr_quotes = 0;
	i = -1;
	while ((*token)[++i])
		if ((*token)[i] == SINGQ || (*token)[i] == DOUBQ)
			nbr_quotes++;
	prod = malloc(ft_strlen(*token) - nbr_quotes + 1);
	i = -1;
	j = 0;
	while ((*token)[++i])
	{
		if ((*token)[i] == SINGQ || (*token)[i] == DOUBQ)
		{
			j++;
			continue ;
		}
		prod[i - j] = (*token)[i];
	}
	prod[i - j] = '\0';
	free(*token);
	*token = prod;
}

/**
*	@brief Splits the prompt in tokens
*	@param s the portion of the prompt to be tolkenized
*/
char	**tokenizer(char *s)
{
	char	**tokens;
	int		i;

	i = -1;
	prompt_neutralizer(s);
	tokens = ft_split(s, SPC);
	while (tokens[++i])
	{
		unquoter(&tokens[i]);
		tokens[i][0] = what_redir_token(tokens[i]);
	}
	return (tokens);
}
