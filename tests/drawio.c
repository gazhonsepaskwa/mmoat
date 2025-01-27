/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:41:02 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 14:41:02 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "tokenizer/tokenizer.h"

int	get_amp_count(char *str)
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

char* replace_ampercent(char *src)
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

void gen_dio_linked_list(t_node *head, char *fp)
{
	int fd;
	t_dio_elem rect;
	t_dio_elem arrow;
	t_node *current;

	current = head;
	fd = drawio_init(fp);
	rect.type = RECT;
	rect.rounded = 0;
	rect.x = 50;
	rect.y = 50;
	rect.w = 100;
	rect.h = 50;
	arrow.id_src = 0;
	arrow.type = ARROW;
	while (current != NULL)
	{
		rect.text = ft_sprintf("|||%s|||", current->val);
		rect.text = replace_ampercent(rect.text);
		arrow.id_dst = drawio_create_elem(fd, &rect);
		drawio_create_elem(fd, &arrow);
		arrow.id_src = arrow.id_dst;
		rect.x += 150;
		free(rect.text);
		current = current->next;
	}
	drawio_end_file(fd);
}
