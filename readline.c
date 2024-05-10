#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;

	line = get_input("shell$>");
	while (line)
	{
		if (line && *line)
		{
			printf("%s\n", line);
		}
		free(line);
		line = get_input("shell$>");
	}
	printf("exit\n");
	rl_clear_history();
	return (0);
}
