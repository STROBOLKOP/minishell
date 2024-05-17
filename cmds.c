#include "./libft/incl/libft.h"
#include <stdbool.h>
#include <stdio.h>

#define PIPE_R 0
#define PIPE_W 1

#define REDIR_IN	1L << 0
#define REDIR_OUT	2L << 1
#define REDIR_APND	3L << 2
#define REDIR_HERE	4L << 3

/* Abstract syntax tree stuff */
typedef struct s_ast		t_ast;
typedef enum e_ast_tag		t_ast_tag;
typedef union u_ast_data	t_ast_data;

typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;

enum e_ast_tag
{
	T_PIPE,
	T_CMD,
	T_ARG,
	T_REDIR,
	T_END
};

struct s_pipe
{
	t_ast	*left;
	t_ast	*right;
};

typedef struct s_redir
{
	char			*str;
	int				flags;
	struct s_redir	*next;
}			t_redir;

struct s_cmd
{
	char	**cmd_av;
	t_redir	*redirs;
};

union u_ast_data
{
	t_cmd	ast_cmd;
	t_pipe	ast_pipe;
};

struct s_ast
{
	t_ast_tag	tag;
	t_ast_data	data;
};

/* Token stuff */
typedef struct s_token
{
	char			*str;
	int				depth;
	t_ast_tag		tag;
}	t_token;

t_token	*create_token(t_token token)
{
	t_token	*ret;

	ret = malloc(sizeof(t_ast));
	if (ret)
		*ret = token;
	return (ret);
}

t_ast	*ast_new_node(t_ast ast)
{
	t_ast	*ret;

	ret = malloc(sizeof(t_ast));
	if (ret)
		*ret = ast;
	return (ret);
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

	node_content = create_token((t_token){"cat", 1, T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"<", 2, T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"INFILE", 2, T_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"|", 0, T_PIPE});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"cat", 1, T_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);
}

size_t	count_cmd_av(t_list *tokens)
{
	size_t	count;
	t_list	*iter;

	if (!tokens)
		return (errno = EINVAL, 0);
	iter = tokens;
	count = 0;
	while (iter)
	{
		if (exact_match(((t_token *)(iter)->content)->str, "|"))
			return (count);
		count++;
		iter = iter->next;
	}
	return (count);
}

void	fill_cmd_av(t_list **tokens, char **cmd_av)
{
	size_t	i;

	i = 0;
	while (*tokens)
	{
		if (exact_match(((t_token *)(*tokens)->content)->str, "|"))
			return ;
		cmd_av[i] = ((t_token *)(*tokens)->content)->str;
		i++;
		(*tokens) = (*tokens)->next;
	}
	cmd_av[i] = NULL;
}

void	make_cmd_list(t_list **cmds, t_list **tokens)
{
	t_cmd	*cmd;
	char	**cmd_av;
	size_t	av_count;
	t_list	redirs;

	while (*tokens)
	{
		av_count = count_cmd_av(*tokens);
		if (errno)
			exit(1);
		if (!av_count)
			return ;
		cmd_av = malloc(sizeof(char *) * (av_count + 1));
		cmd = malloc(sizeof(t_cmd));
		if (errno)
			exit(1);
		fill_cmd_av(tokens, cmd_av);
		if (*tokens)
			(*tokens) = (*tokens)->next;
	}
}

void	print_cmd_list(t_list *cmds)
{
	while (cmds)
	{
	}
}

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

inline static void	print_token(t_token *token)
{
	printf("(%d, %d, %s)", token->depth, token->tag, token->str);
}

void	print_token_list(t_list *tokens)
{
	t_list	*head;

	if (!tokens)
		return ;
	head = tokens;
	printf("(depth, tag, str)\n\t");
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

int	main(int ac, char **av)
{
	t_list	*tokens;
	t_list	*cmds;

	tokens = NULL;
	//make_token_list(&tokens, ac, av);
	make_token_list(&tokens);
	print_token_list(tokens);
	make_cmd_list(&cmds, &tokens);
	return (0);
}
