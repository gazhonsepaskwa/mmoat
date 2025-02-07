/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:15:39 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 09:14:08 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_ast_rect(t_dio_elem *rect)
{
	rect->type = RECT;
	rect->rounded = 0;
	rect->x = 50;
	rect->y = 150;
	rect->w = 150;
	rect->h = 120;
}

void	gen_dio_ast(t_ast_n *head, int fd)
{
	t_elems	*e;

	e = ft_calloc(sizeof(t_elems), 1);
	set_ast_rect(&e->rect);
	e->arrow.type = ARROW;
	e->arrow.id_src = 0;
	e->arrow.id_dst = 0;
	print_ast(head, e, fd);
	free(e->rect.text);
	free(e);
	return ;
}
