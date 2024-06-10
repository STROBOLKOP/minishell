/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 22:08:47 by elias             #+#    #+#             */
/*   Updated: 2024/06/10 18:55:52 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char *name, int flag)
{
	int	fd;

	if (flag == R_IN)
		fd = open(name, O_RDONLY | O_CLOEXEC);
	else if (flag == R_OUT)
		fd = open(name, O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 00666);
	else if (flag == R_APND)
		fd = open(name, O_WRONLY | O_APPEND | O_CLOEXEC | O_CREAT, 00666);
	else
		exit(1);
	return (fd);
}

/* pipe_fd[2] for when we handle here_doc ??? */
void	do_redirs(t_cmd *cmd, int pipe_fd[2])
{
	t_redir	*redirs;
	int		fd;

	(void)pipe_fd;
	redirs = cmd->redirs;
	while (redirs)
	{
		if (redirs->flags != R_HERE)
		{
			fd = open_file(redirs->str, redirs->flags);
			if (errno)
				exit_handler(1);
			if (redirs->flags == R_IN)
			{
				if (dup2(fd, STDIN_FILENO) == -1)
					exit_handler(1);
			}
			else
			{
				if (dup2(fd, STDOUT_FILENO) == -1)
					exit_handler(1);
			}
		}
		redirs = redirs->next;
	}
}

void	ft_execve(t_cmd *cmd, int pipe_fd[2], t_minishell *shell)
{
	//(void)shell;
	if (cmd->next && dup2(pipe_fd[PIPE_W], STDOUT_FILENO) == -1)
		exit_handler(1); // error
	close(pipe_fd[PIPE_W]);
	do_redirs(cmd, pipe_fd);
	check_for_builtins(cmd->cmd_av, &shell->env);
	execvp(cmd->cmd_av[0], cmd->cmd_av);//uncomment before merging
	exit_handler(1); // reached if execve (execpv) had an error.//uncomment before merging
}

void	ft_wait(void)
{
	int	wstat;

	wait(&wstat);
	if (WIFEXITED(wstat))
	{
		g_shell_stats.prev_exit = WEXITSTATUS(wstat);
		/*
		if (WEXITSTATUS(wstat) != 0)
		{
			errno = WEXITSTATUS(wstat);
			exit_handler(errno); // instead of exit, should change variable, and continue to run minishell process
		}
		*/
	}
}

void	ft_run_cmds(t_cmd *cmds, t_minishell *shell)
{
	int	pipe_fd[2];
	int	cpid;
	int	stdin_copy; // copy to restore stdin for later. Maybe need to do this for the other std streams as well.

	stdin_copy = dup(STDIN_FILENO);
	while (cmds)
	{
		if (pipe(pipe_fd) == -1)
			exit_handler(1);
		cpid = fork();
		if (cpid == -1)
			exit_handler(1);
		if (!cpid)
			ft_execve(cmds, pipe_fd, shell);
		close(pipe_fd[PIPE_W]);
		if (dup2(pipe_fd[PIPE_R], STDIN_FILENO) == -1)
			exit_handler(1);
		ft_wait();
		close(pipe_fd[PIPE_R]);
		cmds = cmds->next;
	}
	if (dup2(stdin_copy, STDIN_FILENO) == -1 || close(stdin_copy))
		exit_handler(1);
}
