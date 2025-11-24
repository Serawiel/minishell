/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:26:41 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 14:53:01 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(((ft_gnl_strlen(buffer) - i) + 1) * sizeof(char));
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*extract_line(char *buffer, char c)
{
	char			*line;
	unsigned int	i;

	if (!buffer || !*buffer)
		return (NULL);
	line = malloc((ft_len_line(buffer, c) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < ft_len_line(buffer, c))
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_and_stock(int fd, char **buffer)
{
	char	*temp;
	char	*new_buffer;
	int		bytes_read;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!ft_gnl_strchr(*buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			return (NULL);
		}
		if (bytes_read == 0)
		{
			free(temp);
			return (*buffer);
		}
		temp[bytes_read] = '\0';
		new_buffer = ft_gnl_strjoin(*buffer, temp);
		free(*buffer);
		*buffer = new_buffer;
	}
	free(temp);
	return (*buffer);
}

static void	cleanup_buffer(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd == -1)
		return (cleanup_buffer(&buffer), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_stock(fd, &buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer, '\n');
	if (!line)
		return (cleanup_buffer(&buffer), NULL);
	buffer = trim_buffer(buffer);
	if (!buffer || *buffer == '\0')
		cleanup_buffer(&buffer);
	return (line);
}
