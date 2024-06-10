/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/10 18:54:42 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	check_for_builtins(char **string_av, t_var **env)
{
	if (exact_match(string_av[0], "echo"))
		builtin_echo(string_av);
	else if (exact_match(string_av[0], "cd"))
		builtin_cd(*env);
	else if (exact_match(string_av[0], "pwd"))
		builtin_pwd(*env);
	else if (exact_match(string_av[0], "export"))
		builtin_export(env, string_av[1], string_av[2]);
	else if (exact_match(string_av[0], "unset"))
		builtin_unset(*env, string_av[1]);
	else if (exact_match(string_av[0], "env"))
		builtin_env(env);
	else if (exact_match(string_av[0], "exit"))
		builtin_exit();
	return (0);
}

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
		if (ft_strnstr(env->name, "PWD", 3))
		{
			printf("%s=%s\n", env->name, env->value);
			break ;
		}
		env = env->next;
	}
	g_shell_stats.prev_exit = 0;
	return (0);
	//Do I need to print error when PWD has been unset
	//or do I need to show the correct working directory
	//and figure it out differently?
}

static char	*get_home_path_and_change_dir(t_var *env)
{
	char	*home_path;

	while (env)
	{
		if (ft_strnstr(env->name, "HOME", 4))
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

int	builtin_echo(char **strings_to_echo)
{
	int	iter;

	iter = 2;
	if (ft_strnstr(strings_to_echo[1], "$?", 2))
		printf("%d\n", g_shell_stats.prev_exit);
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

void	builtin_unset(t_var *env, char *var_to_delete)
{
	while (env)
	{
		if (ft_strnstr(env->name, var_to_delete, ft_strlen(var_to_delete)))
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

