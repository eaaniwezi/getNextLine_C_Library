/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarrie <tkarrie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 00:29:15 by tkarrie           #+#    #+#             */
/*   Updated: 2022/01/13 00:29:55 by tkarrie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find_new_line(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*ft_get_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!remainder)
		return (0);
	i = ft_find_new_line(remainder);
	if (remainder[i] == '\0')
	{
		free(remainder);
		return (0);
	}
	new = (char *)malloc(sizeof(char) *(ft_strlen(remainder) - i) + 1);
	if (!new)
		return (NULL);
	while (remainder[i] != '\0')
		new[j++] = remainder[i++];
	new[j] = '\0';
	free(remainder);
	return (new);
}

char	*copy_untill_new_line(char *remainder)
{
	int		i;
	char	*new;

	i = 0;
	if (!remainder)
		return (0);
	i = ft_find_new_line(remainder);
	new = malloc (sizeof(char) * (i + 1));
	if (!new)
		return (0);
	i = 0;
	while (remainder[i] != '\0')
	{
		if (remainder[i] == '\n')
		{
			new[i] = remainder[i];
			i++;
			break ;
		}
		new [i] = remainder [i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static int		count = 1;
	static char		*remainder;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	while (!(ft_strchr(remainder, '\n')) && count > 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1 || (count == 0 && remainder == NULL))
		{
			free(buff);
			return (NULL);
		}
		buff[count] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	free(buff);
	line = copy_untill_new_line(remainder);
	remainder = ft_get_remainder(remainder);
	return (line);
}
