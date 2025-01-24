/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:44:22 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/24 13:47:10 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

char	*ft_strfjoin(char *s1, char *s2)
{
	char			*out;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	ft_free(&s1);
	return (out);
}

char	*ft_strfjoinc(char *s1, char c)
{
	char			*out;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
	{
		out = ft_calloc(2, sizeof(char));
		if (!out)
			return (NULL);
		out[0] = c;
		return (out);
	}
	out = ft_calloc(ft_strlen(s1) + 2, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	out[i] = c;
	ft_free(&s1);
	return (out);
}

char	*ft_strfjoind(char *s1, char *s2)
{
	char			*out;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	ft_free(&s1);
	ft_free(&s2);
	return (out);
}
