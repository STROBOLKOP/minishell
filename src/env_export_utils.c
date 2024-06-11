/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:48 by elias             #+#    #+#             */
/*   Updated: 2024/06/07 19:03:09 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_export_vars(t_var *env_list)
{
	size_t	ret;

	ret = 0;
	while (env_list)
	{
		if (env_list->is_exp)
			ret++;
		env_list = env_list->next;
	}
	return (ret);
}

static void	envp_add_var(char **ret_var, t_var *list_var)
{
	size_t	new_len;
	char	*value;

	new_len = ft_strlen(list_var->name) + ft_strlen(list_var->value) + 1;
	value = malloc(sizeof(char) * (new_len + 1));
	if (!value)
		return ;
	ft_memcpy(value, list_var->name, new_len + 1);
	value[ft_strlen(list_var->name)] = '=';
	*ret_var = value;
}

char	**make_export_envp(t_var *env_list)
{
	size_t	i;
	size_t	count_vars;
	char	**ret;

	count_vars = count_export_vars(env_list);
	ret = malloc(sizeof(char *) * (count_vars + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (env_list && i < count_vars)
	{
		if (env_list->is_exp)
			envp_add_var(&ret[i++], env_list);
		env_list = env_list->next;
	}
	ret[count_vars] = NULL;
	return (ret);
}
