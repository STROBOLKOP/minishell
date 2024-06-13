/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/13 13:30:04 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

static void	builtin_wrapper(int (*func)(t_cmd *, t_minishell *), t_cmd *cmd, t_minishell *shell, int pipe_fd[2]);

static int	new_pwd(t_cmd *cmd, t_minishell *shell)
{
	t_var	*pwd_var;

	(void)cmd;
	pwd_var = env_search_name(shell->env, "PWD");
	if (pwd_var)
		printf("%s\n", pwd_var->value);
	return (0);
}

static int	new_echo(t_cmd *cmd, t_minishell *shell)
{
	size_t	iter;
	bool	nl;

	(void)shell;
	iter = 1;
	if (!cmd->cmd_av[iter])
		return (printf("\n"), 0);
	nl = true;
	// Very simple -n option, but maybe add wrong option detection?
	if (exact_match(cmd->cmd_av[iter], "-n"))
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

static t_var	*env_add_var_only(t_var **env, char *name)
{
	char	*var_name;
	t_var	*node;

	if (!name)
		return (errno = EINVAL, NULL);
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
		{
			var = env_search_name(shell->env, cmd->cmd_av[iter]); // maybe do the searching inside env_add_var_only?
			if (!var)
				var = env_add_var_only(&shell->env, cmd->cmd_av[iter]);
		}
		var->is_exp = true;
		iter++;
	}
	env_update_export(shell);
	return (0);
}

int	check_for_builtins(t_cmd *cmd, t_minishell *shell, int pipe_fd[2])
{
	(void)pipe_fd;
	if (exact_match(cmd->cmd_av[0], "echo"))
		builtin_wrapper(new_echo, cmd, shell, pipe_fd);
	else if (exact_match(cmd->cmd_av[0], "cd"))
		builtin_cd(shell->env); // Still have to create this one.
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
static void	builtin_wrapper(int (*func)(t_cmd *, t_minishell *), t_cmd *cmd, t_minishell *shell, int pipe_fd[2])
{
	int		stdout_copy;

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

/* Left your stuff untouched I believe */

int	builtin_env(t_var **env)
{
	t_var	*current;

	current = *env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	g_shell_stats.prev_exit = 0;
	return (0);
}

int	builtin_pwd(t_var *env)
{
	while (env)
	{
		if (exact_match(env->name, "PWD"))
		{
			printf("%s\n", env->value);
			break ;
		}
		env = env->next;
	}
	g_shell_stats.prev_exit = 0;
	return (0);
	//Do I need to print error when PWD has been unset
	//or do I need to show the correct working directory
	//and figure it out differently?
	//do it with getenv?
}

static char	*get_home_path_and_change_dir(t_var *env)
{
	char	*home_path;

	home_path = NULL;
	while (env)
	{
		if (exact_match(env->name, "HOME"))
		{
			home_path = env->value;
			if (chdir(home_path) != 0)
			{
				if (errno == 2)
					printf("No such file or directory\n");
				g_shell_stats.prev_exit = 1;
				exit_handler(1);
			}
			break ;
		}
		env = env->next;
	}
	return (home_path);
}

static void	set_pwd_to_home_path(t_var *env, char *home_path)
{
	while (env)
	{
		if (ft_strnstr(env->name, "PWD", 3))
		{
			env->value = home_path;
			break ;
		}
		env = env->next;
	}
}

int	builtin_cd(t_var *env)
{
	char	*home_path;

	//make one function to handle cd without arguments
	home_path = get_home_path_and_change_dir(env);
	set_pwd_to_home_path(env, home_path);

	//TO DO: cd with absolute path
	
	//TO DO: cd with relative path

	g_shell_stats.prev_exit = 0;
	return (0);
}

int	builtin_echo(char **strings_to_echo)//also code this without option -n
{
	int	iter;

	printf("builtin_echo\n");
	iter = 2;
	//first check if -n is 
	while (strings_to_echo[iter])
	{
		if (exact_match(strings_to_echo[1], "-n") && strings_to_echo[iter])
			printf("%s ", strings_to_echo[iter]);
		iter++;
	}
//	if (exact_match(strings_to_echo[1], "-n") && !strings_to_echo[iter])
	//	printf("\n");
	g_shell_stats.prev_exit = 0;
	return (0); //is this the correct exit code?
}

void	builtin_unset(t_var *env, char *var_to_delete)//-> env del target
{
	while (env)
	{
		if (ft_strnstr(env->name, var_to_delete, ft_strlen(var_to_delete)))//exact match
		{
			env->prev->next = env->next;
			free(env->name);
			free(env->value);
			free(env);
			g_shell_stats.prev_exit = 0;
			break ;
		}
		env = env->next;
	}
}

static t_var	*create_new_node(char *name_to_export, char *value_to_export)
{
	t_var	*new_var;

	new_var = malloc(sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->name = ft_strdup(name_to_export);
	//ft_strdup is needed because the strings would not be saved if the function ends and when I run the env command again
	new_var->value = ft_strdup(value_to_export); //same here
	new_var->is_exp = true;
	new_var->next = NULL;
	new_var->prev = NULL;
	return (new_var);
}

static void	add_node_back(t_var **env, t_var *node)
{
	t_var	*current;

	current = *env;
	while (current->next)
		current = current->next;
	current->next = node;
	node->prev = current;
}

void	builtin_export(t_var **env, char *name_to_export, char *value_to_export)
{
	t_var	*new_var;

	new_var = create_new_node(name_to_export, value_to_export);
	add_node_back(env, new_var);
	g_shell_stats.prev_exit = 0;
}

