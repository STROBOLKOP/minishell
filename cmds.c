#include "./libft/incl/libft.h"

#define PIPE_R 0
#define PIPE_W 1

#define REDIR_HERE 1 << 0
#define REDIR_FILE 1 << 1
#define REDIR_NBR 1 << 2

typedef struct s_redir
{
	char	*file;
	int		flags;
}			t_redir;

typedef struct s_cmd
{
	char	*path;
	char	**cmd_av;
	t_redir	*redir_in;
	t_redir	*redir_out;
}			t_cmd;

int	main(void)
{
	return (0);
}
