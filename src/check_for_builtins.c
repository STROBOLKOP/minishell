/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/11 18:40:54 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_builtins(char *string)
{
	if (exact_match(string, "echo"))
		printf("You have entered the echo builtin\n");
	else if (exact_match(string, "cd"))
		cd_builtin();
	else if (exact_match(string, "pwd"))
		pwd_builtin();
	else if (exact_match(string, "export"))
		printf("You have entered the EXPORT builtin\n");
	else if (exact_match(string, "unset"))
		printf("You have entered the UNSET builtin\n");
	else if (exact_match(string, "env"))
		env_builtin();
	else if (exact_match(string, "exit"))
		exit_handler(0);
	return (0);
}
