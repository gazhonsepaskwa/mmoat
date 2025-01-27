/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:39 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/27 17:15:39 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawio.h"

void	set_ast_rect(t_dio_elem *rect)
{
	rect->type = RECT;
	rect->rounded = 0;
	rect->x = 50;
	rect->y = 150;
	rect->w = 150;
	rect->h = 100;
}

const char *translate_state(t_state state)
{
	const char	*out;

	if (state == _AND)
		out = "CMD_AND";
	else if (state == _OR)
		out = "CMD_OR";
	else if (state == _PLINE)
		out = "CMD_PIPELINE";
	else if (state == _CMD)
		out = "SIMPLE_CMD";
	else
		out = "UNDEFINED";

	return (out);

}

void print_ast(t_ast_n *node, t_dio_elem *rect, int fd)
{
    int i;
    const char *state;

    if (!node || !rect)
        return;

    state = translate_state(node->state);
    rect->text = ft_sprintf("%s\ntest", state);
    drawio_create_elem(fd, rect);
	
	if (node->state != _PLINE)
	{
		rect->y += rect->h + 50;
		print_ast(node->left, rect, fd);
		rect->x += rect->w + 50;
		print_ast(node->right, rect, fd);
		rect->y -= rect->h + 50;
		rect->x -= rect->w + 50;
	}
	else
	{
		i = 0;
		rect->y += rect->h + 50;
		while (node->pline[i])
		{
			print_ast(node->pline[i++], rect, fd);
			rect->x += rect->w + 50;
		}
	}
}
void	gen_dio_ast(t_ast_n *head, int fd)
{
	t_dio_elem	rect;

	set_ast_rect(&rect);
	print_ast(head, &rect, fd);
	return ;
}
