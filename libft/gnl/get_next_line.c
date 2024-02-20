/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:12:41 by lferro            #+#    #+#             */
/*   Updated: 2024/01/15 14:54:04 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

// read fd and return raw line with \n and the leftover
// from the buffer (stash var)
char	*line_read(int fd, char *buf, char *stash)
{
	int		bread;
	char	*temp_stash;

	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, buf, BUFFER_SIZE);
		if (bread < 0)
			return (NULL);
		else if (bread == 0)
			break ;
		buf[bread] = 0;
		if (!stash)
			stash = ft_strdup("");
		temp_stash = stash;
		stash = ft_strjoin(temp_stash, buf);
		free(temp_stash);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

// SUB_LINE
// params:	raw line to remove residual from
// return:	clean line with \n at the end
char	*sub_line(char *line)
{
	char	*newline;
	int		i;

	i = 0;
	newline = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i] && line[i] != '\n')
	{
		newline[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		newline[i++] = '\n';
	newline[i] = '\0';
	return (newline);
}

// GET_RESIDUAL
// params:	raw line to get residual from
// return:	string after the \n from line
char	*get_residual(char *line)
{
	t_get_residual	var;

	var.i = 0;
	var.j = 0;
	var.residual = malloc(ft_strlen(line) * sizeof(char));
	if (!line)
		return (ft_strdup(""));
	if (!var.residual)
		return (NULL);
	while (line[var.i] && line[var.i] != '\n')
		var.i++;
	if (line[var.i] == '\n')
		var.i++;
	while (line[var.i])
		var.residual[var.j++] = line[var.i++];
	var.residual[var.j] = 0;
	return (var.residual);
}

// GET_NEXT_LINE
// After error handling, get raw line, get residual, cut line.
// params: file descriptor to return line from
// return: current line
char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*stash;
	char		*res;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (freeyator(&stash));
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	line = line_read(fd, buf, stash);
	freeyator(&buf);
	if (!line)
		return (freeyator(&line));
	res = sub_line(line);
	stash = get_residual(line);
	freeyator(&line);
	if (*res == '\0')
		freeyator(&stash);
	if (*res == '\0')
		return (freeyator(&res));
	return (res);
}

char	*freeyator(char **s)
{
	free(*s);
	*s = 0;
	return (NULL);
}

// int main()
// {
// 	int fd = open("file.txt", O_RDONLY);

// 	char	*str;
// 	while((str = get_next_line(fd)))
// 		printf("%s", str);
// 	close(fd);
// 	free(str);

// 	return (0);
// }
