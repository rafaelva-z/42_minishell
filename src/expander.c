/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:21:47 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/10 16:33:26 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *key_word(char *s)
{
	int		i;
	char	*key_wrd;

	i = 0;
	while (s[i] && s[i] != 32 && s[i] != 34)
		i++;
	key_wrd = malloc(i + 1);
	key_wrd[i] = 0;
	i = -1;
	while (s[++i] && s[i] != 32 && s[i] != 34)
		key_wrd[i] = s[i];
	return (key_wrd);
}

static char	*expand(char *s)
{
	char	*key_wrd;
	char	*var;


	key_wrd = key_word(s);
	var = get_env_var_value((const char *)key_wrd);
	if (!var)
	{
		free (key_wrd);
		return (ft_strdup(""));
	}
	free (key_wrd);
	return (ft_strdup(var));
}

char	*expansions(char *prompt, char *first_prompt)
{
	int		i;
	char	*expanded_str;
	char	*prod;

	i = 0;
	expanded_str = NULL;
	while (prompt[i] && (prompt[i] != '$' || is_inside_quotes(prompt, i) == 1))
		i++;
	if (!prompt[i] || !(prompt[i + 1]))
		return (prompt);
	if (prompt[i + 1] == '?')
	{
		prompt[i] = 0;
		expanded_str = ft_strjoin(prompt, ft_itoa(get_env_struct()->exit_status));
		if (prompt == first_prompt)
			free (prompt);
		return (expanded_str);
	}
	prompt[i] = 0;
	expanded_str = ft_strjoin_free(prompt, expand(prompt + i + 1), 2);
	while (prompt[++i] && prompt[i] != ' ' && prompt[i] != '\"')
		;
	prod = ft_strjoin_free(expanded_str, expansions(prompt + i, first_prompt), 3);
	free (prompt);
	return (prod);
}


/*
        dkvdnvdv \0PATH safaf $OTHER
*/