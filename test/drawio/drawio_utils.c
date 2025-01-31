/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:09:16 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/27 15:09:16 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawio.h"

static int	get_char_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*replace_ampercent(char *src)
{
	int		i;
	int		j;
	int		amp_count;
	char	*out;

	i = -1;
	j = 0;
	amp_count = get_char_count(src, '&');
	out = malloc(ft_strlen(src) + amp_count * 4 + 1);
	while (src[++i])
	{
		if (src[i] == '&')
		{
			out[j] = '&';
			out[j + 1] = 'a';
			out[j + 2] = 'm';
			out[j + 3] = 'p';
			out[j + 4] = ';';
			j += 5;
		}
		else
			out[j++] = src[i];
	}
	out[j] = 0;
	free(src);
	return (out);
}

char	*replace_left_red(char *src)
{
	int		i;
	int		j;
	int		redl_count;
	char	*out;

	i = -1;
	j = 0;
	redl_count = get_char_count(src, '<');
	out = malloc(ft_strlen(src) + redl_count * 7 + 1);
	while (src[++i])
	{
		if (src[i] == '<')
		{
			out[j] = '&';
			out[j + 1] = 'a';
			out[j + 2] = 'm';
			out[j + 3] = 'p';
			out[j + 4] = ';';
			out[j + 5] = 'l';
			out[j + 6] = 't';
			out[j + 7] = ';';
			j += 8;
		}
		else
			out[j++] = src[i];
	}
	out[j] = 0;
	free(src);
	return (out);
}
