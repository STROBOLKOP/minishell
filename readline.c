#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
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

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exit_handler(void)
{
	rl_clear_history();
	exit(0);
}

int	main(void)
{
	char	*line;

	signal(SIGINT, sig_handler);
	line = get_input("shell$> ");
	while (line)
	{
		if (exact_match(line, "exit"))
			exit_handler();
		if (line && *line)
		{
			printf("%s\n", line);
		}
		free(line);
		line = get_input("shell$> ");
	}
	printf("exit\n");
	exit_handler();
	return (0);
}
