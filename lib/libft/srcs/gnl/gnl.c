/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:45:42 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 12:24:09 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "gnl.h"

static char	*f_free(char *res, char *buffer, int ret)
{
	char	*tmp;

	buffer[ret] = '\0';
	tmp = ft_strjoin_gnl(res, buffer);
	free(res);
	return (tmp);
}

static char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = f_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = buffer[i];
	i++;
	line[i] = '\0';
	return (line);
}

static char	*ft_next(char *buffer)
{
	char	*buf;
	int		start;
	int		i;

	start = 0;
	buf = NULL;
	while (buffer[start] && buffer[start] != '\n')
		start++;
	if (!buffer[start++])
	{
		free(buffer);
		return (NULL);
	}
	if ((ft_strlen(buffer) - start) != 0)
	{
		buf = f_calloc(sizeof(char), ft_strlen(buffer) - start + 1);
		if (!buf)
			return (NULL);
	}
	i = 0;
	ft_strlcat(buf, buffer, -1);
	if (buf)
		buf[i] = '\0';
	free(buffer);
	return (buf);
}

static char	*ft_readfile(int fd, char *res, int ret)
{
	char	*buf;

	if (!res)
		res = f_calloc(1, sizeof(char));
	if (!res)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(res);
			free(buf);
			return (NULL);
		}
		res = f_free(res, buf, ret);
		if (ft_strchr_index(buf, '\n') != -1)
			break ;
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd, int del)
{
	static char	*buffer[256];
	char		*line;

	if (del == 1)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 255)
		return (NULL);
	buffer[fd] = ft_readfile(fd, buffer[fd], 1);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	if (buffer[fd] == NULL && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
// void	free_buf(char **tab)
// {
// 	if (tab && *tab)
// 	{
// 		free(*tab);
// 		*tab = NULL;
// 	}
// }
//
// char	*build_tab(char *tab, char *buffer, int i)
// {
// 	char	*ret;
// 	size_t	t_len;
// 	size_t	b_len;
//
// 	b_len = ft_gstrlen(buffer, -2);
// 	t_len = ft_gstrlen(tab, i);
// 	ret = malloc(b_len + t_len + 1);
// 	if (!ret)
// 	{
// 		free(tab);
// 		return (NULL);
// 	}
// 	if (tab)
// 	{
// 		ft_strlcpy(ret, tab, t_len + 1);
// 		ft_strlcat(&ret[t_len], buffer, b_len + t_len + 1);
// 		free(tab);
// 	}
// 	else
// 		ft_strlcpy(ret, buffer, b_len + 1);
// 	return (ret);
// }
//
// char	*get_the_line(char **tab, int i)
// {
// 	char	*line;
// 	char	*new_tab;
// 	size_t	len;
// 	char	*nl_pos;
//
// 	nl_pos = ft_strichr(*tab, '\n', i);
// 	if (!nl_pos)
// 		return (NULL);
// 	len = nl_pos - *tab + 1;
// 	line = malloc(len + 1);
// 	if (!line)
// 		return (NULL);
// 	ft_strlcpy(line, *tab, len + 1);
// 	line[len] = '\0';
// 	new_tab = ft_strdup(*tab + len);
// 	if (!new_tab)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	free(*tab);
// 	*tab = new_tab;
// 	return (line);
// }
//
// int	read_file(int fd, char **tab, int i)
// {
// 	char	buffer[BUFFER_SIZE + 1];
// 	ssize_t	bytes_read;
//
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read <= 0)
// 	{
// 		if (bytes_read == -1)
// 			free_buf(&tab[fd]);
// 		return (bytes_read);
// 	}
// 	buffer[bytes_read] = '\0';
// 	tab[fd] = build_tab(tab[fd], buffer, i);
// 	if (!tab[fd])
// 		return (-1);
// 	return (bytes_read);
// }
//
// char	*get_next_line(int fd)
// {
// 	static char	*tab[256];
// 	char		*next_line;
// 	int			i;
//
// 	i = -1;
// 	next_line = NULL;
// 	if (fd < 0 || fd >= 256 || BUFFER_SIZE == 0)
// 		return (NULL);
// 	while (++i || 1)
// 	{
// 		next_line = get_the_line(&tab[fd], i);
// 		if (next_line)
// 			return (next_line);
// 		if (read_file(fd, tab, i) <= 0)
// 			break ;
// 	}
// 	if (tab[fd] && *tab[fd])
// 	{
// 		next_line = tab[fd];
// 		tab[fd] = NULL;
// 		return (next_line);
// 	}
// 	free(tab[fd]);
// 	tab[fd] = NULL;
// 	return (NULL);
// }
