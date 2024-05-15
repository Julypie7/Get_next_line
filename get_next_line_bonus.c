/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:38:46 by ineimatu          #+#    #+#             */
/*   Updated: 2024/03/05 13:14:10 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
int main()
{
	int fd;
	int fd1;
	char	*line;
	char	*line1;

	fd = open("nextline.txt", O_RDONLY);
	fd1 = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	line1 = get_next_line(fd1);
	while (line != NULL && line1 != NULL)
	{
			printf("%s", line);
			printf("%s", line1);
			free(line);
			free(line1);
	}
	return (0);
}
*/

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = ft_fill_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_clean_line(stash[fd]);
	if (!line)
		return (ft_free(&stash[fd]));
	stash[fd] = ft_new_stash(stash[fd]);
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
