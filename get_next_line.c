/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:47:38 by agladkov          #+#    #+#             */
/*   Updated: 2023/02/07 20:20:31 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *bufferjoin(char *buffer, char *str)
{
	char *tmp;

	if (!buffer)
		buffer = (char *)ft_calloc(1, 1);
	tmp = buffer;
	buffer = ft_strjoin(buffer, str);
	free(tmp);
	tmp = NULL;
	return (buffer);
}

char	*read_line(int fd, char *buffer)
{
	ssize_t	len;
	char *out;

	out = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	len = 1;
	while (len > 0)
	{
		len = read(fd, out, BUFFER_SIZE);
		if ((ft_strlen(buffer) == 0 && len == 0) || len < 0)
		{
			free(out);
			return (NULL);
		}
		out[len] = 0;
		buffer = bufferjoin(buffer, out);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(out);
	return (buffer);
}

char	*get_line(char *buffer)
{
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\0')
		return (ft_substr(buffer, 0, len));
	return (ft_substr(buffer, 0, ++len));
}

char	*rebuffer(char *buffer)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	if (buffer[len] == '\n')
		len++;
	tmp = buffer;
	buffer = ft_substr(buffer, len, ft_strlen(buffer) - len);
	free(tmp);
	tmp = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char *out;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = read_line(fd, buf);
	if (!buf)
		return (NULL);
	out = get_line(buf);
	buf = rebuffer(buf);
	if (!buf)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
