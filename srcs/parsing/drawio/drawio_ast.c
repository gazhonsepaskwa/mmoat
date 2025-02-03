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
	t_elems	e;

	set_ast_rect(&e.rect);
	e.arrow.type = ARROW;
	e.arrow.id_src = 0;
	e.arrow.id_dst = 0;
	print_ast(head, &e, fd);
	return ;
}
