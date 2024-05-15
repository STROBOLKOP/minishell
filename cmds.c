#include "./libft/incl/libft.h"
#include <stdio.h>

#define PIPE_R 0
#define PIPE_W 1

#define REDIR_HERE 1 << 0

/* Abstract syntax tree stuff */
typedef struct s_ast		t_ast;
typedef enum e_ast_tag		t_ast_tag;
typedef union u_ast_data	t_ast_data;

typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;

enum e_ast_tag
{
	AST_PIPE,
	AST_CMD,
	AST_REDIR,
	AST_END
};

struct s_pipe
{
	t_ast	*left;
	t_ast	*right;
};

typedef struct s_redir
{
	char	*str;
	int		flags;
}			t_redir;

struct s_cmd
{
	char	*path;
	char	**cmd_av;
	t_redir	*redir_in;
	t_redir	*redir_out;
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

/*
void	make_token_list(t_list **tokens, int ac, char **av)
{
	int		i;
	t_token	*node_content;
	t_list	*node;

	i = 0;
	while (i < ac && av[i])
	{
		node_content = create_token((t_token){av[i], 0, AST_END});
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

	node_content = create_token((t_token){"<", 2, AST_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"INFILE", 2, AST_REDIR});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"cat", 1, AST_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"|", 0, AST_PIPE});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);

	node_content = create_token((t_token){"cat", 1, AST_CMD});
	node = ft_lstnew(node_content);
	ft_lstadd_back(tokens, node);
}

inline static void	print_token(t_token *token)
{
	printf("(%d, %d, %s)", token->depth, token->tag, token->str);
}

void	print_token_list(t_list *tokens)
{
	printf("(depth, tag, str)\n\t");
	while (tokens)
	{
		print_token(tokens->content);
		if (tokens->next)
			printf(" -> \n\t");
		tokens = tokens->next;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_list	*tokens;

	tokens = NULL;
	//make_token_list(&tokens, ac, av);
	make_token_list(&tokens);
	print_token_list(tokens);
	return (0);
}
