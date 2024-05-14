#include "./libft/incl/libft.h"
#include <stdio.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <asm-generic/errno-base.h>

#ifndef DEBUG
# define DEBUG 0
#endif

#define PIPE_R 0
#define PIPE_W 1

typedef struct s_cmd
{
	char	*path;
	char	**cmd_av;
}			t_cmd;

typedef struct s_pipex_data
{
	t_list	*cmds;
	int		in_fd;
	int		out_fd;
	int		pipe[2];
	char	**paths;
	char	*delim;
}			t_pipex_data;

void	ft_free_split(char **split)
{
	size_t	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static void	ft_free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_free_split(cmd->cmd_av);
	free(cmd->path);
	free(cmd);
}

static void	ft_free_cmds(t_list *cmds)
{
	t_list	*iter;

	iter = cmds;
	while (iter)
	{
		iter = cmds->next;
		ft_free_cmd(cmds->content);
		free(cmds);
		cmds = iter;
	}
}

static void	ft_free_pipex(t_pipex_data *pipex)
{
	ft_free_split(pipex->paths);
	ft_free_cmds(pipex->cmds);
}

void	ft_exit_handler(t_pipex_data *pipex, int print_err, char *err_msg)
{
	if (print_err && errno)
		perror(err_msg);
	ft_free_pipex(pipex);
	exit(errno);
}

static unsigned int	ft_count_args(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;
	int				q_flag;

	i = 0;
	count = 0;
	q_flag = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			q_flag = 1 - q_flag;
		if (s[i] && (q_flag || (!q_flag && s[i] != c)))
			count++;
		while (s[i] && (q_flag || (!q_flag && s[i] != c)))
		{
			i++;
			if (s[i] == '\'')
				q_flag = 1 - q_flag;
		}
		while (s[i] && (s[i] == c))
			i++;
	}
	return (count);
}

static void	*ft_free_arg_split(char **split, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end)
		free(split[i++]);
	free(split);
	return (NULL);
}

static size_t	ft_fill_split(const char *s, char **word, char c, size_t *i)
{
	size_t	w_len;
	int		q_flag;

	w_len = 0;
	q_flag = 0;
	if (s[w_len] == '\'')
		q_flag = 1;
	while (s[w_len + q_flag] && (q_flag || (!q_flag && s[w_len + q_flag] != c)))
	{
		w_len++;
		if (q_flag && s[w_len + 1] == '\'')
			break ;
	}
	*word = ft_substr(s, q_flag, w_len);
	if (!(*word))
		return (0);
	*i += w_len + 2 * q_flag;
	return (w_len);
}

char	**ft_arg_split(char const *s, char c)
{
	size_t	w_count;
	size_t	i;
	size_t	w_idx;
	char	**res;

	w_count = ft_count_args(s, c);
	res = malloc(sizeof(char *) * (w_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	w_idx = 0;
	while (s[i] && w_idx < w_count)
	{
		while (s[i] && (s[i] == c))
			i++;
		if (!ft_fill_split(&s[i], &res[w_idx++], c, &i))
			return (ft_free_arg_split(res, w_idx - 1));
	}
	res[w_idx] = 0;
	return (res);
}

static char	*ft_get_path_str(char **envp)
{
	size_t	i;
	char	**tmp;
	char	*path_str;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			tmp = ft_split(envp[i], '=');
			if (!tmp)
				return (errno = ENOMEM, NULL);
			break ;
		}
		i++;
	}
	if (!tmp || !tmp[1])
		return (errno = EINVAL, NULL);
	path_str = tmp[1];
	free(tmp[0]);
	free(tmp);
	return (path_str);
}

static void	ft_get_paths(t_pipex_data *pipex, char **envp)
{
	char	*path_str;
	size_t	i;

	path_str = ft_get_path_str(envp);
	if (!path_str)
		return ;
	pipex->paths = ft_split(path_str, ':');
	free(path_str);
	i = 0;
	while (pipex->paths[i])
	{
		if (pipex->paths[i][ft_strlen(pipex->paths[i])] != '/')
		{
			path_str = pipex->paths[i];
			pipex->paths[i] = ft_strjoin(path_str, "/");
			free(path_str);
		}
		i++;
	}
}

static char	*ft_find_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	size_t	i;

	if (!access(cmd, X_OK))
	{
		cmd_path = ft_strdup(cmd);
		if (!cmd_path)
			return (errno = ENOMEM, NULL);
		return (cmd_path);
	}
	if (cmd[0] == '/')
		return (errno = ENOENT, NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (errno = ENOMEM, NULL);
		if (!access(cmd_path, X_OK))
			return (errno = 0, cmd_path);
		free(cmd_path);
		i++;
	}
	return (errno = ENOENT, NULL);
}

static void	ft_add_cmd_node(t_pipex_data *pipex, char *cmd_path, char **cmd_av)
{
	t_cmd	*cmd_node_data;
	t_list	*cmd;

	cmd_node_data = malloc(sizeof(t_cmd));
	if (!cmd_node_data)
		return (free(cmd_path),
			ft_free_split(cmd_av), ft_exit_handler(pipex, DEBUG, "malloc"));
	cmd_node_data->cmd_av = cmd_av;
	cmd_node_data->path = cmd_path;
	cmd = ft_lstnew(cmd_node_data);
	if (!cmd)
		return (free(cmd_node_data), free(cmd_path),
			ft_free_split(cmd_av), ft_exit_handler(pipex, DEBUG, "malloc"));
	ft_lstadd_back(&pipex->cmds, cmd);
}

void	ft_make_cmd_lst(t_pipex_data *pipex, int ncmds, char **av, char **envp)
{
	int		i;
	char	*cmd_path;
	char	**cmd_av;

	ft_get_paths(pipex, envp);
	if (errno)
		ft_exit_handler(pipex, 1, "envp");
	i = 0;
	while (i < ncmds && av[i])
	{
		cmd_av = ft_arg_split(av[i], ' ');
		if (!cmd_av)
			ft_exit_handler(pipex, DEBUG, "split failure");
		cmd_path = ft_find_cmd_path(cmd_av[0], pipex->paths);
		if (!cmd_path)
			(ft_putstr_fd("command not found: ", STDERR_FILENO),
				ft_putendl_fd(cmd_av[0], STDERR_FILENO),
				ft_free_split(cmd_av),
				ft_exit_handler(pipex, DEBUG, "find_cmd"));
		ft_add_cmd_node(pipex, cmd_path, cmd_av);
		i++;
	}
}

static void	ft_execve(t_pipex_data *pipex, t_list *cmd_node, char **envp)
{
	t_cmd	*cmd;

	if (cmd_node->next && dup2(pipex->pipe[PIPE_W], STDOUT_FILENO) == -1)
		ft_exit_handler(pipex, 0, NULL);
	if (!cmd_node->next && dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		ft_exit_handler(pipex, 0, NULL);
	cmd = cmd_node->content;
	close(pipex->pipe[PIPE_W]);
	close(pipex->out_fd);
	execve(cmd->path, cmd->cmd_av, envp);
	ft_exit_handler(pipex, DEBUG, "execve");
}

static void	ft_wait(t_pipex_data *pipex)
{
	int	wstat;

	wait(&wstat);
	if (WIFEXITED(wstat))
	{
		if (WEXITSTATUS(wstat) != 0)
		{
			errno = WEXITSTATUS(wstat);
			ft_exit_handler(pipex, DEBUG, "error in child");
		}
	}
}

static void	ft_here_doc(t_pipex_data *pipex)
{
	char	*line;

	if (!pipex->delim)
		return ;
	if (pipe(pipex->pipe) == -1)
		ft_exit_handler(pipex, DEBUG, "pipe");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (!ft_strncmp(line, pipex->delim, ft_strlen(pipex->delim))
			&& ft_strlen(line) != ft_strlen(pipex->delim))
		{
			free(line);
			break ;
		}
		write(pipex->pipe[PIPE_W], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipex->pipe[PIPE_W]);
	pipex->in_fd = pipex->pipe[PIPE_R];
}

void	ft_run_cmd(t_pipex_data *pipex, char **envp)
{
	t_list	*cmd_node;
	int		cpid;

	ft_here_doc(pipex);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		ft_exit_handler(pipex, DEBUG, "dup2");
	close(pipex->in_fd);
	cmd_node = pipex->cmds;
	while (cmd_node)
	{
		if (pipe(pipex->pipe) == -1)
			ft_exit_handler(pipex, DEBUG, "pipe");
		cpid = fork();
		if (cpid == -1)
			ft_exit_handler(pipex, DEBUG, "fork");
		if (!cpid)
			ft_execve(pipex, cmd_node, envp);
		close(pipex->pipe[PIPE_W]);
		if (dup2(pipex->pipe[PIPE_R], STDIN_FILENO) == -1)
			ft_exit_handler(pipex, DEBUG, "dup2");
		ft_wait(pipex);
		close(pipex->pipe[PIPE_R]);
		cmd_node = cmd_node->next;
	}
	close(pipex->out_fd);
}

void	ft_init_pipex(t_pipex_data *pipex, int ac, char **av, char **envp)
{
	pipex->cmds = NULL;
	pipex->paths = NULL;
	pipex->delim = NULL;
	if (ft_strnstr(av[1], "here_doc", ft_strlen("here_doc")))
		pipex->delim = av[2];
	ft_make_cmd_lst(pipex, ac - (3 + (pipex->delim != NULL)),
		&av[2 + (pipex->delim != NULL)], envp);
	if (!pipex->delim)
		pipex->out_fd = open(av[ac - 1],
				O_WRONLY | O_TRUNC | O_CLOEXEC | O_CREAT, 00666);
	else
		pipex->out_fd = open(av[ac - 1],
				O_WRONLY | O_APPEND | O_CLOEXEC | O_CREAT, 00666);
	if (pipex->out_fd == -1)
		return (ft_exit_handler(pipex, 1, av[ac - 1]));
	pipex->in_fd = 0;
	if (!pipex->delim)
	{
		pipex->in_fd = open(av[1], O_RDONLY | O_CLOEXEC);
		if (pipex->in_fd == -1)
			(close(pipex->out_fd), ft_exit_handler(pipex, 1, av[1]));
	}
	if (errno)
		(close(pipex->in_fd), close(pipex->out_fd),
			ft_exit_handler(pipex, DEBUG, "ft_make_cmd_lst"));
}

static void	ft_print_args(int ac, char **av)
{
	int	i;

	ft_printf("Program input arguments:\n");
	i = 0;
	while (i < ac)
		ft_printf("%s\n", av[i++]);
	ft_printf("\n");
}

static void	ft_print_pipex(t_pipex_data *pipex)
{
	t_list	*cmd_node;
	t_cmd	*cmd;
	size_t	i;

	ft_printf("Linked list of commands:\n");
	cmd_node = pipex->cmds;
	while (cmd_node)
	{
		cmd = cmd_node->content;
		ft_printf("cmd: %s\tav: ", cmd->path);
		i = 0;
		while (cmd->cmd_av[i])
		{
			ft_printf("%s", cmd->cmd_av[i++]);
			if (cmd->cmd_av[i])
				ft_printf(", ");
		}
		ft_printf("\n");
		cmd_node = cmd_node->next;
	}
	ft_printf("\n");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex_data	pipex;

	if (ac < 4)
		return (ft_printf("Usage: %s <infile> "
				"\"cmd1 <args>\" \"cmd2 <args>\" ..."
				"<outfile>\n", av[0]), 1);
	if (DEBUG)
		ft_print_args(ac, av);
	ft_init_pipex(&pipex, ac, av, envp);
	if (DEBUG)
		ft_print_pipex(&pipex);
	ft_run_cmd(&pipex, envp);
	ft_exit_handler(&pipex, 1, NULL);
	return (0);
}

