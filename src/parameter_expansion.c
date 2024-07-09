/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:27:03 by pclaus            #+#    #+#             */
/*   Updated: 2024/07/09 15:38:28 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>

void	calculate_start_and_end(t_token **iter, int *start, int *end)
{
	int	i;

	i = 0;
	while ((*iter)->str[i] != '\0')
	{
		if ((*iter)->str[i] == '$')
		{
			*start = i;
			while ((*iter)->str[i] != ' ' && (*iter)->str[i] != '"')
				i++;
			*end = i;
		}
		i++;
	}
}

char	*get_trimmed_parameter(int start, int end, t_token **iter,
		t_minishell *shell)
{
	char	*trimmed_parameter;

	(void)shell;
	trimmed_parameter = malloc((end - start + 1) * sizeof(char *));
	if (!trimmed_parameter)
		return (NULL); //malloc failure
	ft_strlcpy(trimmed_parameter, (*iter)->str + start, end - start + 1);
	return (trimmed_parameter);
}

char	*get_expanded_string(int start, t_token **iter, char *env_value,
		char *trimmed_parameter)
{
	char	*string_to_expand;
	char	*expanded_string;
	int		total_len;

	string_to_expand = ft_strdup(env_value);
	total_len = ft_strlen(string_to_expand) + ft_strlen((*iter)->str)
		- ft_strlen(trimmed_parameter);
	expanded_string = malloc((total_len + 1) * sizeof(char *));
	if (!expanded_string)
		return (NULL); //malloc failure
	ft_strlcpy(expanded_string, (*iter)->str, start + 1);
	ft_strlcat(expanded_string, string_to_expand, total_len + 1);
	ft_strlcat(expanded_string, (*iter)->str + start
		+ ft_strlen(trimmed_parameter), total_len + 1);
	return (expanded_string);
}

static void	expand_single_quotes(t_token *iter, t_var *env_iter)
{
	char	*string_to_expand;

	while (env_iter)
	{
		if (exact_match(iter->str + 1, env_iter->name) == true)
		{
			string_to_expand = ft_strdup(env_iter->value);
			free(iter->str);
			iter->str = string_to_expand;
			return ;
		}
		env_iter = env_iter->next;
	}
}

static void	expand_double_quotes(t_token *iter, t_var *env_iter,
		t_minishell *shell)
{
	char	*trimmed_parameter;
	char	*expanded_string;
	int		start;
	int		end;

	while (env_iter)
	{
		calculate_start_and_end(&iter, &start, &end);
		trimmed_parameter = get_trimmed_parameter(start, end, &iter, shell);
		if (exact_match(trimmed_parameter + 1, env_iter->name) == true)
		{
			expanded_string = get_expanded_string(start, &iter, env_iter->value,
					trimmed_parameter);
			free(iter->str);
			iter->str = expanded_string;
			free(trimmed_parameter);
			return ;
		}
		free(trimmed_parameter);
		env_iter = env_iter->next;
	}
}

void	process_token(t_token *iter, t_minishell *shell)
{
	t_var	*env_iter;

	env_iter = shell->env;
	if (iter->tag == CMD && ft_strchr(iter->str, '$')
		&& (ft_strlen(iter->str) > 1))
		expand_single_quotes(iter, env_iter);
	if (iter->tag == DOUBLE_Q && ft_strchr(iter->str, '$')
		&& (ft_strlen(iter->str) > 1))
		expand_double_quotes(iter, env_iter, shell);
}

void	expand_parameters(t_token **token, t_minishell *shell)
{
	t_token	*iter;

	iter = *token;
	while (iter)
	{
		process_token(iter, shell);
		if (iter->next)
			iter = iter->next;
		else
			break ;
	}
}
