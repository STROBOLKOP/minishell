/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_test_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:38:39 by efret             #+#    #+#             */
/*   Updated: 2024/07/10 14:54:49 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_token_delim(int c, int quote)
{
	if (quote)
		return (0);
	return (is_meta_character(c) || ft_isspace(c));
}

int	update_quote_state(int c, int *quote)
{
	if (*quote)
	{
		if (c == '\'' || c == '\"')
			return (*quote = Q_NONE, 1);
	}
	else
	{
		if (c == '\'')
			return (*quote = Q_SINGLE, 1);
		else if (c == '\"')
			return (*quote = Q_DOUBLE, 1);
	}
	return (0);
}

char	*get_expand_value(char *line, size_t *i, t_var *env)
{
	char	*var_name;
	t_var	*var;

	(*i)++;
	if (!line[*i] || ft_isspace(line[*i]))
		return ("$");
	if (ft_isdigit(line[*i]))
		return (NULL);
	var_name = NULL;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
	{
		if (ft_strjoin_char(&var_name, line[*i]))
			exit(1); // Error I guess
		(*i)++;
	}
	var = env_search_name(env, var_name);
	free(var_name);
	if (var)
		return (var->value);
	return (NULL);
}

int	ft_strjoin_var(char **tok_str, char *line, size_t *i, t_var *env)
{
	char	*tmp;
	char	*value;

	value = get_expand_value(line, i, env);
	if (!value)
		return (0);
	if (!*tok_str)
	{
		*tok_str = ft_strdup(value);
	}
	else
	{
		tmp = *tok_str;
		*tok_str = ft_strjoin(tmp, value);
		free(tmp);
	}
	if (!tok_str)
		return (1); // Error
	return (0);
}

t_token	*next_token(char *str, t_minishell *shell)
{
	t_token			*tok;
	static size_t	i = 0;
	int				quote;

	if (!str)
		return (i = 0, NULL);
	if (!str[i])
		return (NULL);
	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = ft_strdup("");
	if (!tok->str)
		return (free(tok), NULL);
	while (str[i] && ft_isspace(str[i]))
		i++;
	quote = Q_NONE;
	while (str[i])
	{
		if (is_token_delim(str[i], quote))
			break ;
		if (update_quote_state(str[i], &quote))
		{
			i++;
			continue ;
		}
		if (quote != Q_SINGLE && str[i] == '$')
		{
			if (ft_strjoin_var(&tok->str, str, &i, shell->env))
				return (i = 0, NULL);
		}
		else
			ft_strjoin_char(&tok->str, str[i++]);
	}
	if (quote)
		return (free(tok), i = 0, NULL);
	return (tok);
}

t_token	*test_lexer(char *line, t_minishell *shell)
{
	t_token	*token;
	t_token	*ret_tokens;

	ret_tokens = NULL;
	token = next_token(line, shell);
	while (token)
	{
		add_token_to_end(&ret_tokens, token);
		token = next_token(line, shell);
	}
	next_token(NULL, shell);
	return (ret_tokens);
}
