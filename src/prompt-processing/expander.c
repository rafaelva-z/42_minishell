/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:21:47 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/15 15:40:25 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*key_word(char *s, int *quote, int *i)
{
	int		j;
	char	*key_wrd;
	(void)quote;

	j = 0;
	while (s[j] && s[j] != ' ' && s[j] != '\"' && s[j] != '$')
		j++;
	key_wrd = malloc(j + 1);
	key_wrd[j] = 0;
	j = -1;
	while (s[++j] && s[j] != ' ' && s[j] != '\"' && s[j] != '$')
		key_wrd[j] = s[j];
	// if (s[j] == '\"')
	// 	*quote = 1;
	*i += j + 1;
	return (key_wrd);
}

static char	*expand(char *s, int *i)
{
	char	*key_wrd;
	char	*var;
	int		quote;
	char	*prod;

	quote = 0;
	prod = NULL;
	key_wrd = key_word(s, &quote, i);
	if (!ft_strncmp(key_wrd, "?", 2))
	{
		free (key_wrd);
		return (ft_itoa(get_env_struct()->exit_status));
	}
	var = get_env_var_value((const char *)key_wrd);
	if (!var)
	{
		free (key_wrd);
		return (NULL);
	}
	free (key_wrd);
	if (quote)
		prod = "\"";
	return (ft_strjoin_free(var, prod, 0));
}

static void	limiter_masker(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (is_inside_quotes(prompt, i) != 1 && prompt[i] == '<' && prompt[i + 1] == '<')
			i += 3;
		else
			continue ;
		while (prompt[i] && !(prompt[i] == ' ' && is_inside_quotes(prompt, i) == 0))
		{
			if (prompt[i] == '$')
				prompt[i] = -1;
			i++;
		}
	}
}
/**
 * @brief	converts all '$' between SQUOTES to -1
*/
static void	squotes_masker(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
		if (prompt[i] == '$' && is_inside_quotes(prompt, i) == 1)
			prompt[i] = -1;
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

static char	*expansion(char *prompt, int rec, int i, char *expnd_str)
{
	char	*prd;

	if (!prompt || !*prompt)
		return (NULL);
	if (!expansion_check_str(prompt))
	{
		if (rec == 0)
			return (prompt);
		return (ft_strdup(prompt));
	}
	while (prompt[i] && prompt[i] != '$')
		i++;
	prompt[i] = '\0';
	expnd_str = ft_strjoin_free(prompt, expand(prompt + i + 1, &i), 2);
	prd = ft_strjoin_free(expnd_str, expansion(prompt + i, rec + 1, 0, NULL), 3);
	if (rec == 0)
		free (prompt);
	return (prd);
}

void	expansion_manager(char **prompt)
{
	int		i;
	char	*temp;

	i = -1;
	if (!expansion_check_str(*prompt))
		return ;
	expansion_prep(prompt, -1, 0);
	squotes_masker(*prompt);
	limiter_masker(*prompt);
	*prompt = expansion(*prompt, 0, 0, NULL);
	temp = *prompt;
	while (temp[++i])
	{
		if (temp[i] == -1)
			temp[i] = '$';
	}
	printf("-THE F'IN PROMPT: %s\n", *prompt);
}
