/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:09:16 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:36:08 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

void	write_ampercent(char *out)
{
	out[0] = '&';
	out[1] = 'a';
	out[2] = 'm';
	out[3] = 'p';
	out[4] = ';';
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
			write_ampercent(&out[j]);
			j += 5;
		}
		else
			out[j++] = src[i];
	}
	out[j] = 0;
	free(src);
	return (out);
}

void	write_left_redi(char *out)
{
	out[0] = '&';
	out[1] = 'a';
	out[2] = 'm';
	out[3] = 'p';
	out[4] = ';';
	out[5] = 'l';
	out[6] = 't';
	out[7] = ';';
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
			write_left_redi(&out[j]);
			j += 8;
		}
		else
			out[j++] = src[i];
	}
	out[j] = 0;
	free(src);
	return (out);
}
