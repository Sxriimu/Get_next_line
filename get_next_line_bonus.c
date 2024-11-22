/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:30:15 by sxriimu           #+#    #+#             */
/*   Updated: 2024/11/22 18:30:16 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *str)
{
	char	*new_line;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

char	*get_newline(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	new_str = NULL;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	len = ft_strlen(str);
	if (str[i] == '\n' && str[i + 1] != '\0')
	{
		new_str = malloc(sizeof(char) * (len - i + 1));
		if (new_str == NULL)
			return (NULL);
		j = 0;
		while (str[++i] != '\0')
			new_str[j++] = str[i];
		new_str[j] = '\0';
	}
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str[MAX_FD];
	char		*buffer;
	char		*new_line;
	ssize_t		bits;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD - 1)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		bits = read(fd, buffer, BUFFER_SIZE);
		if (bits < 0)
			return (free(buffer), NULL);
		if (bits == 0)
			break ;
		buffer[bits] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer);
		if (ft_strchr(str[fd], '\n') != NULL)
			break ;
	}
	new_line = get_line(str[fd]);
	str[fd] = get_newline(str[fd]);
	return (free(buffer), new_line);
}
