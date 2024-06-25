/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:18:29 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:25 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static size_t	ft_strlen_newline(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		if (s[len++] == '\n')
			break ;
	return (len);
}

static int	ft_append_line(char **line, char *buf)
{
	char	*tmp_line_cpy;
	size_t	buf_cpy_len;
	size_t	line_len;

	line_len = 0;
	tmp_line_cpy = *line;
	if (tmp_line_cpy)
		line_len = ft_strlen(tmp_line_cpy);
	buf_cpy_len = ft_strlen_newline(buf);
	*line = malloc(sizeof(char) * (line_len + buf_cpy_len + 1));
	if (!*line)
		return (errno = ENOMEM, -1);
	ft_memcpy(*line, tmp_line_cpy, line_len);
	ft_memcpy(&((*line)[line_len]), buf, buf_cpy_len);
	(*line)[line_len + buf_cpy_len] = 0;
	ft_memcpy(buf, &buf[buf_cpy_len], BUFFER_SIZE - buf_cpy_len);
	ft_bzero(&buf[BUFFER_SIZE - buf_cpy_len], buf_cpy_len);
	if (tmp_line_cpy)
		free(tmp_line_cpy);
	if ((*line)[line_len + buf_cpy_len - 1] != '\n')
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffers[1024][BUFFER_SIZE + 1];
	char		*line;
	int			read_return;

	line = NULL;
	if (buffers[fd][0])
		if (ft_append_line(&line, buffers[fd]))
			return (line);
	while (1)
	{
		read_return = read(fd, buffers[fd], BUFFER_SIZE);
		if (read_return < 0)
		{
			if (line)
				free(line);
			ft_bzero(buffers[fd], BUFFER_SIZE);
			errno = ENOENT;
			return (NULL);
		}
		if (read_return == 0)
			return (line);
		if (ft_append_line(&line, buffers[fd]))
			return (line);
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file.\n");
		return (0);
	}
	int	fd2 = open("test2.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file.\n");
		return (0);
	}
	int	fd3 = open("test3.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Could not open file.\n");
		return (0);
	}
	int	files[3] = {fd, fd2, fd3};
	for (int i = 0; i < 6; i++)
	{
		line = get_next_line(files[i % 3]);
		printf("%s", line);
		if (line)
			free(line);
	}
	close(fd);
	close(fd2);
	close(fd3);
	return (0);
}
*/
