/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_linklist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:41:02 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/27 17:16:53 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawio.h"

void	set_ll_rect(t_dio_elem *rect)
{
	rect->type = RECT;
	rect->rounded = 0;
	rect->x = 50;
	rect->y = 50;
	rect->w = 100;
	rect->h = 50;
}

void	gen_dio_linked_list(t_node *head, int fd)
{
	t_dio_elem	rect;
	t_dio_elem	arrow;
	t_node		*current;

	current = head;
	set_ll_rect(&rect);
	arrow.id_src = 0;
	arrow.type = ARROW;
	while (current != NULL)
	{
		rect.text = ft_sprintf("%s", current->val);
		rect.text = replace_ampercent(rect.text);
		arrow.id_dst = drawio_create_elem(fd, &rect);
		drawio_create_elem(fd, &arrow);
		arrow.id_src = arrow.id_dst;
		rect.x += 150;
		free(rect.text);
		current = current->next;
	}
}
