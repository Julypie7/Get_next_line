/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:34:19 by ineimatu          #+#    #+#             */
/*   Updated: 2024/04/23 11:14:02 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_clean_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = ft_new_stash(stash);
	return (line);
}

char	*ft_fill_stash(int fd, char *stash)
{
	char	*buff;
	int		readres;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (ft_free(&stash));
	buff[0] = '\0';
	readres = 1;
	while (!(ft_strchr(buff, '\n')) && readres > 0)
	{
		readres = read(fd, buff, BUFFER_SIZE);
		if (readres == -1)
		{
			free(buff);
			return (ft_free(&stash));
		}
		if (readres > 0)
		{
			buff[readres] = '\0';
			stash = ft_strjoin(stash, buff);
		}
	}
	free(buff);
	return (stash);
}

char	*ft_clean_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while ((stash[i]) && (stash[i] != '\n'))
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_new_stash(char *stash)
{
	int		i;
	char	*newstash;

	i = 0;
	if (!stash)
		return (NULL);
	while ((stash[i]) && (stash[i] != '\n'))
		i++;
	if (stash[i] == '\n')
		i++;
	newstash = ft_substr(stash, i, ft_strlen(stash) - i);
	ft_free(&stash);
	if (!newstash)
		return (NULL);
	return (newstash);
}

int main()
{
	int fd;
	char	*line;

	fd = open("nextline.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
			printf("%s", line);
			free(line);
	}
	return (0);
}
