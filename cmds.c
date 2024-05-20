#include "./libft/incl/libft.h"
#include <stdbool.h>
#include <stdio.h>

#define PIPE_R 0
#define PIPE_W 1

typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;

typedef enum e_tag
{
	T_PIPE,
	T_CMD,
	T_ARG,
	T_REDIR,
	T_END
}	t_tag;

typedef struct s_redir
{
	char			*str;
	int				flags;
}			t_redir;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APND,
	R_HERE,
}	t_redir_type;

struct s_cmd
{
	char	**cmd_av;
	t_list	*redirs;
};

/* Token stuff */
typedef struct s_token
{
	char			*str;
	t_tag			tag;
}	t_token;

inline static int	get_token_tag(t_list *token_node)
{
	t_token	*token;

	token = token_node->content;
	return (token->tag);
}

inline static char	*get_token_str(t_list *token_node)
{
	t_token *token;
	
	token = token_node->content;
	return (token->str);
}

inline static char	**get_cmd_av(t_list *cmds)
{
	t_cmd	*cmd;

	cmd = cmds->content;
	return (cmd->cmd_av);
}

inline static t_list	*get_cmd_redirs(t_list *cmds)
{
	t_cmd	*cmd;

	cmd = cmds->content;
	return (cmd->redirs);
}

inline static void	print_token(t_token *token)
{
	printf("(%d, %s)", token->tag, token->str);
}

t_token	*create_token(t_token token)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token));
	if (ret)
		*ret = token;
	return (ret);
}

void	free_token_node(void *content)
{
	return ;
}

bool	exact_match(char *s, char *to_match)
{
	size_t	s_len;
	size_t	to_match_len;
	size_t	i;

	s_len = ft_strlen(s);
	to_match_len = ft_strlen(to_match);
	if (s_len != to_match_len)
		return (false);
	i = 0;
	while (s[i] && to_match[i])
	{
		if (s[i] != to_match[i])
			return (false);
		else
			i++;
	}
	return (true);
}

/*
void	make_token_list(t_list **tokens, int ac, char **av)
{
	int		i;
	t_token	*node_content;
	t_list	*node;

	i = 0;
	while (i < ac && av[i])
	{
		node_content = create_token((t_token){av[i], 0, T_END});
		if (!node_content)
			exit(1); // Should free and stuff
		node = ft_lstnew(node_content);
		if (!node)
			(free(node_content), exit(1));
		ft_lstadd_back(tokens, node);
		i++;
	}
}
*/

void	make_token_list(t_list **tokens)
{
	t_token	*node_content;
	t_list	*node;

	node_content = create_token((t_token){"cat", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"-e", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"<", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"INFILE", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"|", T_PIPE});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"tail", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"-n", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){">", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"OUTFILE", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"<", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"INFILE2", T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"3", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"|", T_PIPE});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"head", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"-n", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"5", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"|", T_PIPE});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"wc", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"-l", T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);
}

size_t	count_pipe_parts(t_list *tokens)
{
	size_t	count;

	if (!tokens)
		return (errno = EINVAL, 0);
	if (exact_match(get_token_str(tokens), "|"))
		return (0);
	count = 1;
	while (tokens)
	{
		if (exact_match(get_token_str(tokens), "|"))
		{
			if (tokens->next && exact_match(get_token_str(tokens->next), "|"))
				return (errno = EINVAL, 0);
			count++;
		}
		tokens = tokens->next;
	}
	return (count);
}

void	clean_pipe_part_list(t_list **pipe_parts)
{
	t_list	*pipe;
	t_list	*prev;
	size_t	i;

	i = 0;
	while (pipe_parts[i])
	{
		prev = pipe_parts[i];
		pipe = prev->next;
		while (pipe)
		{
			if (exact_match(get_token_str(pipe), "|"))
			{
				ft_lstdelone(pipe, free_token_node);
				prev->next = NULL;
				break ;
			}
			prev = pipe;
			pipe = pipe->next;
		}
		i++;
	}
}

t_list	**make_pipe_part_list(t_list *tokens)
{
	t_list	**ret;
	size_t	part_count;
	size_t	i;

	part_count = count_pipe_parts(tokens);
	if (errno)
		exit(1);// error, handle freeing and exit
	ret = malloc(sizeof(t_list *) * (part_count + 1));
	if (!ret)
		return (NULL);
	i = 0;
	ret[i] = tokens;
	ret[part_count] = NULL;
	while (tokens)
	{
		if (exact_match(get_token_str(tokens), "|"))
		{
			tokens = tokens->next;
			ret[++i] = tokens;
		}
		tokens = tokens->next;
	}
	clean_pipe_part_list(ret);
	return (ret);
}

size_t	count_cmd_av(t_list *tokens)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (get_token_tag(tokens) != T_REDIR)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	add_cmd_node(t_list **cmds, t_cmd *cmd)
{
	t_list	*cmd_node;

	cmd_node = ft_lstnew(cmd);
	if (!cmd_node)
		exit(1); //error, here we go again.
	ft_lstadd_back(cmds, cmd_node);
}

t_cmd	*make_cmd_from_content(char **cmd_av, t_list *redirs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit(1); // Free them stuff yo.
	*cmd = (t_cmd){cmd_av, redirs};
	return (cmd);
}

void	add_redir_node(t_list **redirs, t_redir *redir)
{
	t_list	*redir_node;

	redir_node = ft_lstnew(redir);
	if (!redir_node)
		exit(1); // you know the drill
	ft_lstadd_back(redirs, redir_node);
}

t_redir	*make_redir_from_content(char *str,int flag)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(1);
	*redir = (t_redir){str, flag};
	return (redir);
}

void	add_new_redir_node(t_list **redirs, t_list **tokens)
{
	t_redir	*redir;
	char	*redir_op;
	char	*redir_name;
	int		flags;

	redir_op = get_token_str(*tokens);
	*tokens = (*tokens)->next;
	redir_name = get_token_str(*tokens);
	if (exact_match(redir_op, "<"))
		flags = R_IN;
	else if (exact_match(redir_op, ">"))
		flags = R_OUT;
	else if (exact_match(redir_op, "<<"))
		flags = R_HERE;
	else if (exact_match(redir_op, ">>"))
		flags = R_APND;
	redir = make_redir_from_content(redir_name, flags);
	add_redir_node(redirs, redir);
}

void	fill_cmd_content(char **cmd_av, t_list **redirs, t_list *tokens)
{
	size_t	i;

	i = 0;
	while (tokens)
	{
		if (get_token_tag(tokens) != T_REDIR)
			cmd_av[i++] = get_token_str(tokens);
		else
			add_new_redir_node(redirs, &tokens);
		tokens = tokens->next;
	}
}

void	make_cmd_list(t_list **cmds, t_list **pipe_parts)
{
	t_cmd	*cmd;
	t_list	*redirs;
	char	**cmd_av;
	size_t	count_av;
	size_t	i;

	i = 0;
	while (pipe_parts[i])
	{
		redirs = NULL;
		count_av = count_cmd_av(pipe_parts[i]);
		if (!count_av)
			exit(1); // exit because part had only redirect info. Maybe check that when setting the tags?
		cmd_av = malloc(sizeof(char *) * (count_av + 1));
		if (!cmd_av)
			exit(1); // Same stuff here;
		cmd_av[count_av] = NULL;
		fill_cmd_content(cmd_av, &redirs, pipe_parts[i]);
		cmd = make_cmd_from_content(cmd_av, redirs);
		add_cmd_node(cmds, cmd);
		i++;
	}
}

void	print_redir_list(t_list *redirs)
{
	t_redir	*redir;

	while (redirs)
	{
		redir = redirs->content;
		printf("(%d, %s)", redir->flags, redir->str);
		if (redirs->next)
			printf(" -> ");
		redirs = redirs->next;
	}
}

void	print_cmd_list(t_list *cmds)
{
	int	count;

	while (cmds)
	{
		count = printf("Command: ");
		for (int i = 0; get_cmd_av(cmds)[i]; i++)
			count += printf("%s ", get_cmd_av(cmds)[i]);
		printf("%*sRedirs: ", 30 - count, "");
		print_redir_list(get_cmd_redirs(cmds));
		printf("\n");
		cmds = cmds->next;
	}
}

void	print_token_list(t_list *tokens)
{
	t_list	*head;

	if (!tokens)
		return ;
	head = tokens;
	printf("(tag, str)\n\t");
	while (tokens)
	{
		print_token(tokens->content);
		if (tokens->next)
			printf(" -> \n\t");
		tokens = tokens->next;
	}
	tokens = head;
	printf("\n");
	while (tokens)
	{
		printf("%s", ((t_token *)(tokens->content))->str);
		if (tokens->next)
			printf(" ");
		tokens = tokens->next;
	}
	printf("\n");
}

void	print_pipe_parts(t_list	**pipe_parts)
{
	size_t	i;

	if (!pipe_parts)
		return ;
	i = 0;
	while (pipe_parts[i])
		print_token_list(pipe_parts[i++]);
}

int	main(int ac, char **av)
{
	t_list	*tokens;
	t_list	*cmds;
	t_list	**pipe_parts;

	tokens = NULL;
	cmds = NULL;
	make_token_list(&tokens);
	pipe_parts = make_pipe_part_list(tokens);
	print_pipe_parts(pipe_parts);
	make_cmd_list(&cmds, pipe_parts);
	print_cmd_list(cmds);
	return (0);
}
