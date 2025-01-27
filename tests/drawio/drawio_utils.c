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

static int	get_amp_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '&')
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
	amp_count = get_amp_count(src);
	out = malloc(ft_strlen(src) + amp_count * 4);
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
	return (out);
}


