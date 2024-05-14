#include "./libft/incl/libft.h"

#define PIPE_R 0
#define PIPE_W 1

#define REDIR_HERE 1 << 0

typedef struct s_ast		t_ast;
typedef enum e_ast_tag		t_ast_tag;
typedef struct s_pipe		t_pipe;
typedef struct s_cmd		t_cmd;
typedef union u_ast_data	t_ast_data;

enum e_ast_tag
{
	AST_PIPE,
	AST_CMD,
	AST_END
};

struct s_pipe
{
	t_ast	*left;
	t_ast	*right;
};

typedef struct s_redir
{
	char	*token;
	int		flags;
}			t_redir;

struct s_cmd
{
	char	*path;
	char	**cmd_av;
	t_redir	*redir_in;
	t_redir	*redir_out;
};

int	main(void)
{
	return (0);
}
