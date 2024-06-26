/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/26 16:06:35 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	builtin_wrapper(int (*func)(t_cmd *, t_minishell *), t_cmd *cmd,
				t_minishell *shell, int pipe_fd[2]);

static int	new_pwd(t_cmd *cmd, t_minishell *shell)
{
	char	*pwd_val;

	(void)cmd;
	(void)shell;
	pwd_val = getcwd(NULL, 0);
	printf("%s\n", pwd_val);
	free(pwd_val);
	return (0);
}

static int	new_echo(t_cmd *cmd, t_minishell *shell)
{
	size_t	iter;
	bool	nl;

	(void)shell;
	iter = 1;
	nl = true;
	if (cmd->cmd_av[iter] && exact_match(cmd->cmd_av[iter], "-n"))
	{
		nl = false;
		iter++;
	}
	while (cmd->cmd_av[iter])
	{
		printf("%s", cmd->cmd_av[iter++]);
		if (cmd->cmd_av[iter])
			printf(" ");
	}
	if (nl)
		printf("\n");
	return (0);
}

static int	new_env(t_cmd *cmd, t_minishell *shell)
{
	size_t	i;

	(void)cmd;
	i = 0;
	while (shell->export_env[i])
		printf("%s\n", shell->export_env[i++]);
	return (0);
}

static int	new_unset(t_cmd *cmd, t_minishell *shell)
{
	size_t	iter;
	t_var	*to_unset;

	iter = 1;
	while (cmd->cmd_av[iter])
	{
		to_unset = env_search_name(shell->env, cmd->cmd_av[iter]);
		env_del_target(&shell->env, to_unset);
		iter++;
	}
	return (0);
}

t_var	*env_add_var_only(t_var **env, char *name)
{
	char	*var_name;
	t_var	*node;

	if (!name)
		return (errno = EINVAL, NULL);
	node = env_search_name(*env, name);
	if (node)
		return (node);
	var_name = ft_calloc(ft_strlen(name) + 2, sizeof(char));
	if (!var_name)
		return (errno = ENOMEM, NULL);
	ft_strlcpy(var_name, name, ft_strlen(name) + 2);
	node = create_env_var(var_name, &var_name[ft_strlen(name)], false);
	if (!node)
		exit(1); // Error handling
	env_add_back(env, node);
	return (node);
}

/* Technically should print them sorted */
static void	export_print(t_minishell *shell)
{
	t_var	*var;

	var = shell->env;
	while (var)
	{
		if (var->is_exp)
		{
			printf("declare -x %s", var->name);
			if (var->value && var->value[0])
				printf("=\"%s\"", var->value);
			printf("\n");
		}
		var = var->next;
	}
}

static int	new_export(t_cmd *cmd, t_minishell *shell)
{
	size_t	iter;
	t_var	*var;

	iter = 1;
	if (!cmd->cmd_av[iter])
		export_print(shell);
	while (cmd->cmd_av[iter])
	{
		if (ft_strchr(cmd->cmd_av[iter], '='))
			var = env_add_var(&shell->env, cmd->cmd_av[iter], NULL);
		else
			var = env_add_var_only(&shell->env, cmd->cmd_av[iter]);
		var->is_exp = true;
		iter++;
	}
	env_update_export(shell);
	return (0);
}

void	update_path(t_var **dest_node, t_var **source_node, t_minishell *shell,
		char *string)
{
	char	*new_path;

	new_path = malloc(ft_strlen(string) + ft_strlen((*source_node)->value) + 1);
	if (!new_path)
		return ;
	ft_strlcpy(new_path, string, ft_strlen(string) + 1);
	ft_strlcat(new_path, (*source_node)->value, (ft_strlen(new_path)
				+ ft_strlen((*source_node)->value) + 1));
	*dest_node = env_add_var(&shell->env, new_path, NULL);
	free(new_path);
}

static void	builtin_cd_no_arg(t_var **pwd_node, t_var **home_node,
		t_var **oldpwd_node, t_minishell *shell)
{
	*home_node = env_search_name(shell->env, "HOME");
	*pwd_node = env_search_name(shell->env, "PWD");
	*oldpwd_node = env_search_name(shell->env, "OLDPWD");
	update_path(oldpwd_node, pwd_node, shell, "OLDPWD=");
	update_path(pwd_node, home_node, shell, "PWD=");
	if (chdir((*home_node)->value))
	{
		if (errno == 2)
			printf("No such file or directory\n");
		g_shell_stats.prev_exit = 1;
		exit_handler(1); //error handling
	}
	env_update_export(shell);
}

static void	builtin_cd_arg(t_var **pwd_node, t_var **oldpwd_node,
		t_cmd *cmd, t_minishell *shell)
{
	char	new_pwd[200];
	char	*new_pwd_string;

	*pwd_node = env_search_name(shell->env, "PWD");
	*oldpwd_node = env_search_name(shell->env, "OLDPWD");
	if (chdir(cmd->cmd_av[1]))
	{
		if (errno == 2)
			printf("No such file or directory\n");
		g_shell_stats.prev_exit = 1;
		exit_handler(1); //error handling
	}
	update_path(oldpwd_node, pwd_node, shell, "OLDPWD=");
	getcwd(new_pwd, sizeof(new_pwd));
	new_pwd_string = malloc(sizeof(char) * (ft_strlen(new_pwd) + 5));
	if (!new_pwd_string)
		return ;
	ft_strlcpy(new_pwd_string, "PWD=", 5);
	ft_strlcat(new_pwd_string, new_pwd, ft_strlen("PWD=") + ft_strlen(new_pwd)
			+ 1);
	*pwd_node = env_add_var(&shell->env, new_pwd_string, *pwd_node);
	*pwd_node = env_search_name(shell->env, "PWD");
	free(new_pwd_string);
	env_update_export(shell);
}
static int	new_cd(t_cmd *cmd, t_minishell *shell)
{
	t_var	*home_node;
	t_var	*pwd_node;
	t_var	*oldpwd_node;

	home_node = NULL;
	pwd_node = NULL;
	oldpwd_node = NULL;
	if (!cmd->cmd_av[1])
		builtin_cd_no_arg(&pwd_node, &home_node, &oldpwd_node, shell);
	else 
		builtin_cd_arg(&pwd_node, &oldpwd_node, cmd, shell);
	g_shell_stats.prev_exit = 0;
	return (0);
}

int	check_for_builtins(t_cmd *cmd, t_minishell *shell, int pipe_fd[2])
{
	(void)pipe_fd;
	if (exact_match(cmd->cmd_av[0], "echo"))
		builtin_wrapper(new_echo, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "cd"))
		builtin_wrapper(new_cd, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "pwd"))
		builtin_wrapper(new_pwd, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "export"))
		builtin_wrapper(new_export, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "unset"))
		builtin_wrapper(new_unset, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "env"))
		builtin_wrapper(new_env, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "exit"))
		printf("Exit Builtin\n");
	else
		return (0);
	return (1);
}
static void	builtin_wrapper(int (*func)(t_cmd *, t_minishell *), t_cmd *cmd,
		t_minishell *shell, int pipe_fd[2])
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (cmd->next && dup2(pipe_fd[PIPE_W], STDOUT_FILENO) == -1)
		exit_handler(1); //error
	do_redirs(cmd);
	g_shell_stats.prev_exit = func(cmd, shell);
	close_redirs(cmd);
	close(pipe_fd[PIPE_W]);
	if (dup2(pipe_fd[PIPE_R], STDIN_FILENO) == -1 || close(pipe_fd[PIPE_R]))
		exit_handler(1);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1 || close(stdout_copy))
		exit_handler(1);
}
