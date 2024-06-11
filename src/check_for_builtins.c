/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:40:59 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/11 19:24:59 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

// Need t_cma *cmd to know if the output needs to be redirected.
// before doing the actual builtin stuff, redir fds.
// After doing the actual builting stuff, prepare the input for the next cmd.
// (even if there isn't actually a next one.)
// and "reset" the stdout (with the copy).
static void	new_pwd(t_cmd *cmd, t_var **env, int pipe_fd[2])
{
	int		stdout_copy;
	t_var	*pwd_var;

	stdout_copy = dup(STDOUT_FILENO);
	if (cmd->next && dup2(pipe_fd[PIPE_W], STDOUT_FILENO) == -1)
		exit_handler(1); //error
	do_redirs(cmd);

	/* Start of actual builtin stuff */
	pwd_var = env_search_name(*env, "PWD");
	if (pwd_var)
		printf("%s\n", pwd_var->value);
	/* End of actual builtin stuff */

	close_redirs(cmd);
	close(pipe_fd[PIPE_W]);
	if (dup2(pipe_fd[PIPE_R], STDIN_FILENO) == -1)
		exit_handler(1);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1 || close(stdout_copy))
		exit_handler(1);
}

// Again same redirs stuff, so maybe some wrapping function would be wise
// Still needs '-n' option
static void	new_echo(t_cmd *cmd, int pipe_fd[2])
{
	size_t	iter;
	bool	nl;
	int		stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (cmd->next && dup2(pipe_fd[PIPE_W], STDOUT_FILENO) == -1)
		exit_handler(1); //error
	do_redirs(cmd);

	/* Start of actual builtin stuff */
	iter = 1;
	nl = true;
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
	/* End of actual builtin stuff */

	close_redirs(cmd);
	close(pipe_fd[PIPE_W]);
	if (dup2(pipe_fd[PIPE_R], STDIN_FILENO) == -1)
		exit_handler(1);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1 || close(stdout_copy))
		exit_handler(1);
}

int	check_for_builtins(t_cmd *cmd, t_var **env, int pipe_fd[2])
{
	(void)pipe_fd;
	if (exact_match(cmd->cmd_av[0], "echo"))
		return (new_echo(cmd, pipe_fd), 1);
	else if (exact_match(cmd->cmd_av[0], "cd"))
		return (builtin_cd(*env), 1);
	else if (exact_match(cmd->cmd_av[0], "pwd"))
		return (new_pwd(cmd, env, pipe_fd), 1);
	else if (exact_match(cmd->cmd_av[0], "export"))
		return (builtin_export(env, cmd->cmd_av[1], cmd->cmd_av[2]), 1);
	else if (exact_match(cmd->cmd_av[0], "unset"))
		return (builtin_unset(*env, cmd->cmd_av[1]), 1);
	else if (exact_match(cmd->cmd_av[0], "env"))
		return (builtin_env(env), 1);
	else if (exact_match(cmd->cmd_av[0], "exit"))
		return (printf("Exit builtin\n"), 1);
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

