/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:48:02 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 11:56:38 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "gnl.h"

int	ft_strchr_index(char *s, int c)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

void	*f_calloc(int size, int nb)
{
	void	*ptr;
	int		i;

	i = 0;
	ptr = malloc(size * nb);
	if (!ptr)
		return (NULL);
	while (i < size * nb)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	j = 0;
	i = -1;
	while (s1 && s1[++i])
	{
		str[j] = s1[i];
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
// size_t	ft_gstrlen(const char *str, int j)
// {
// 	size_t	i;
//
// 	i = 0;
// 	if (!str)
// 		return (0);
// 	if (j == 0 || j == -2)
// 	{
// 		while (str[i])
// 			i++;
// 		return (i);
// 	}
// 	else
// 	{
// 		if (j > 0)
// 			j--;
// 		if (j != 0)
// 			i += (BUFFER_SIZE * j) - 1;
// 		while (str[i])
// 			i++;
// 		return (i);
// 	}
// }
//
// char	*ft_strichr(const char *s, int c, int i)
// {
// 	char	*str;
// 	char	ch;
//
// 	if (!s)
// 		return (0);
// 	if (i > 0)
// 		i--;
// 	ch = c;
// 	str = (char *)s;
// 	if (i != 0)
// 		str += (BUFFER_SIZE * i) - 1;
// 	while (*str)
// 	{
// 		if (*str == ch)
// 			return (str);
// 		str++;
// 	}
// 	if ((ch == 0) && (*str == 0))
// 		return (str);
// 	return (0);
// }
