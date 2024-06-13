/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/13 13:34:03 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell_stats	g_shell_stats;

void	non_interactive(char *filename, t_minishell *shell)
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
		ft_run_cmds(cmds, shell);
		free_cmds(&cmds);
		free_tokens(&tokens);
		free(line);
		line = get_next_line(file);
	}
	exit(0);
}

void	load_rc(char *filename, t_minishell *shell)
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
		ft_run_cmds(cmds, shell);
		free_cmds(&cmds);
		free_tokens(&tokens);
		free(line);
		line = get_next_line(file);
	}
	close(file);
}

void	shell_lvl(t_minishell *shell)
{
	char	*token;
	char	*tmp;
	t_var	*var;

	var = env_search_name(shell->env, "SHLVL");
	if (!var)
	{
		token = ft_strdup("SHLVL=1");
		if (!token)
			exit_handler(1);
		env_add_var(&shell->env, token, NULL);
		return (free(token));
	}
	tmp = ft_itoa(ft_atoi(var->value) + 1);
	if (!tmp)
		return ;
	token = ft_strjoin("SHLVL=", tmp);
	if (!token)
		return (free(tmp));
	var = env_add_var(&shell->env, token, NULL);
	if (!var)
		exit_handler(1);// error Handling
	var->is_exp = true;
	return (free(tmp), free(token));
}

void	shell_init(t_minishell *shell, char **envp)
{
	shell->env = NULL;
	env_load(&shell->env, envp);
	shell_lvl(shell);
	memset(&g_shell_stats, 0, sizeof(t_shell_stats));
	shell->export_env = make_export_envp(shell->env);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	shell;

	shell_init(&shell, envp);
	if (ac == 2)
		non_interactive(av[1], &shell);
	if (ac > 2)
		exit_handler(0);
	load_rc(".minishellrc", &shell);
	interactive(&shell);
	return (0);
}
