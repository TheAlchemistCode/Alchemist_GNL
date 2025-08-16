/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:52:57 by clyon             #+#    #+#             */
/*   Updated: 2025/08/14 17:52:57 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_01_stash_builder(int fd, char *stash, char *buffer);
static char	*_02_stash_trunc(char *work_line);
static char	*_03_ft_strchr(char *s, int c);


/* 
 * _01_stash_builder:
 * Reads from the file descriptor into the buffer until either a newline
 * is found or there is no more data to read. Appends each chunk to the stash.
 * Returns the updated stash or NULL on error.
 */
static char	*_01_stash_builder(int fd, char *stash, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
		{
			if (b_read == -1)
				return (free(stash), NULL);
			break ;
		}
		buffer[b_read] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
		if (_03_ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*_02_stash_trunc(char *work_line)
{
	ssize_t	i;
	char	*stash;

	i = 0;
	while (work_line[i] != '\n' && work_line[i] != '\0')
		i++;
	if (work_line[i] == '\0' || work_line[i + 1] == '\0')
		return (NULL);
	stash = ft_substr(work_line, i + 1, ft_strlen(work_line) - (i + 1));
	if (!stash || *stash == '\0')
	{
		free(stash);
		return (NULL);
	}
	work_line[i + 1] = '\0';
	return (stash);
}

static char	*_03_ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*work_line;
	char		*buffer;
	static char	*stash;
	char		*temp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
	}
	work_line = _01_stash_builder(fd, stash, buffer);
	free(buffer);
	if (!work_line)
		return (NULL);
	temp = _02_stash_trunc(work_line);
	stash = temp;
	return (work_line);
}

/*#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
