/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:25:52 by clyon             #+#    #+#             */
/*   Updated: 2025/08/14 18:25:52 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*_01_stash_builder(int fd, char *stash, char *buffer);
static char	*_02_stash_trunc(char *line);
static char	*_03_ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	char		*buffer;
	char		*temp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		free(buffer);
		stash[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _01_stash_builder(fd, stash[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	temp = _02_stash_trunc(line);
	free(stash[fd]);
	stash[fd] = temp;
	return (line);
}

static char	*_01_stash_builder(int fd, char *stash, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (_03_ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*_02_stash_trunc(char *work_line)
{
	char		*stash;
	ssize_t		i;

	i = 0;
	while (work_line[i] != '\n' && work_line[i] != '\0')
		i++;
	if (work_line[i] == '\0' || work_line[i + 1] == '\0')
		return (NULL);
	stash = ft_substr(work_line, i + 1, ft_strlen(work_line) - i - 1);
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
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}
