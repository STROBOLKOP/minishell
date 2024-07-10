/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/07/10 16:08:17 by efret            ###   ########.fr       */
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
		tokens = lexer(line, shell);
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
		tokens = lexer(line, shell);
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
	int		lvl;
	char	*tmp;
	t_var	*var;

	var = env_search_name(shell->env, "SHLVL");
	if (!var)
	{
		var = env_add_var2(&shell->env, "SHLVL", "1", true);
		if (!var)
			exit_handler(1); // error
		return ;
	}
	lvl = ft_atoi(var->value) + 1;
	if (lvl > 999)
	{
		printf("minishell: Warning: shell level (%i) too high, resetting to 1\n", lvl);
		lvl = 1;
	}
	if (lvl < 0)
		lvl = 0;
	tmp = ft_itoa(lvl);
	if (!tmp)
		return ;
	var = env_add_var2(&shell->env, "SHLVL", tmp, true);
	if (!var)
		exit_handler(1);// error Handling
	return (free(tmp));
}

void	old_pwd(t_minishell *shell)
{
	t_var	*var;

	var = env_search_name(shell->env, "OLDPWD");
	if (!var)
		var = env_add_var2(&shell->env, "OLDPWD", NULL, true);
}

void	init_pwd(t_minishell *shell)
{
	char	*pwd_val;
	t_var	*var;

	pwd_val = getcwd(NULL, 0);
	if (!pwd_val)
		exit_handler(1); // Error
	var = env_add_var2(&shell->env, "PWD", pwd_val, true);
	free(pwd_val);
	if (!var)
		exit_handler(1); // Error
}

void	init_path(t_minishell *shell)
{
	t_var	*var;
	char	*dft_p;

	dft_p = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	var = env_search_name(shell->env, "PATH");
	if (!var)
		var = env_add_var2(&shell->env, "PATH", dft_p, false);
}

void	shell_init(t_minishell *shell, char **envp)
{
	shell->env = NULL;
	env_load(&shell->env, envp);
	shell_lvl(shell);
	init_pwd(shell);
	old_pwd(shell);
	init_path(shell);
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
