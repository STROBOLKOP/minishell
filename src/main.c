/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/05 10:13:28 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	non_interactive(char *filename, char **envp)
{
	int		file;
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return ;
	line = get_next_line(file);
	while (line)
	{
		cmds = NULL;
		tokens = lexer(line);
		make_cmd_list(&cmds, tokens);
		ft_run_cmds(cmds, envp);
		free_cmds(&cmds);
		free_tokens(&tokens);
		free(line);
		line = get_next_line(file);
	}
	exit(0);
}

void	load_rc(char *filename, char **envp)
{
	int		file;
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	file = open(filename, O_RDONLY);
	if (file == -1)
		return ;
	line = get_next_line(file);
	while (line)
	{
		cmds = NULL;
		tokens = lexer(line);
		make_cmd_list(&cmds, tokens);
		ft_run_cmds(cmds, envp);
		free_cmds(&cmds);
		free_tokens(&tokens);
		free(line);
		line = get_next_line(file);
	}
}

int	main(int ac, char **av, char **envp)
{
	/*
	if (ac == 2)
		non_interactive(av[1], envp);
	if (ac > 2)
		exit_handler(0);
	(void)av;
	load_rc(".minishellrc", envp);
	interactive(envp);
	*/
	(void)ac;
	(void)av;
	t_var	*env_list;
	env_load(&env_list, envp);
	return (0);
}
