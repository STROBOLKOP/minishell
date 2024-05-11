/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/11 11:43:18 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_builtins(char *string)
{
	if (exact_match(string, "echo"))
		printf("You have entered the echo builtin\n");
	if (exact_match(string, "cd"))
		printf("You have entered the CD builtin\n");
	if (exact_match(string, "pwd"))
		printf("You have entered the PWD builtin\n");
	if (exact_match(string, "export"))
		printf("You have entered the EXPORT builtin\n");
	if (exact_match(string, "unset"))
		printf("You have entered the UNSET builtin\n");
	if (exact_match(string, "env"))
		printf("You have entered the ENV builtin\n");
	if (exact_match(string, "exit"))
		printf("You have entered the EXIT builtin\n");
	return (0);
}
