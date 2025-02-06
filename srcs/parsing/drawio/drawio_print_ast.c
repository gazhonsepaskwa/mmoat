/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_print_ast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:54:31 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/29 09:54:31 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_node_txt(t_ast_n *node)
{
	t_dio_node	txt;
  static char *subsh;
	char		    *out;

	txt = get_cmd_txt(node);
  if (node->sh == true)
    subsh = " (subsh) ";
  else
    subsh = "";
	out = ft_sprintf("%s%s%s%s%s", txt.st, txt.cmd, txt.args,
	      subsh, txt.files);
	free(txt.cmd);
	free(txt.args);
	free(txt.files);
	return (out);
}

void	draw_bin_part(t_ast_n *node, t_elems *e, int fd, int node_id)
{
	e->rect.y += e->rect.h + 50;
	e->arrow.id_dst = print_ast(node->left, e, fd);
	e->arrow.id_src = node_id;
	drawio_create_elem(fd, &e->arrow);
	e->rect.x += e->rect.w + 50;
	e->arrow.id_dst = print_ast(node->right, e, fd);
	e->arrow.id_src = node_id;
	drawio_create_elem(fd, &e->arrow);
	e->rect.y -= e->rect.h + 50;
	if (node->state == _CMD)
		e->rect.x -= e->rect.w + 50;
}

void	draw_pline_part(t_ast_n *node, t_elems *e, int fd, int node_id)
{
	int	i;

	i = 0;
	e->rect.y += e->rect.h + 50;
	while (node->pline && node->pline[i])
	{
		e->arrow.id_dst = print_ast(node->pline[i++], e, fd);
		e->arrow.id_src = node_id;
		drawio_create_elem(fd, &e->arrow);
		e->rect.x += e->rect.w + 50;
	}
}

int	print_ast(t_ast_n *node, t_elems *e, int fd)
{
	int	node_id;

	if (!node)
		return (-1);
	e->rect.text = get_node_txt(node);
	node_id = drawio_create_elem(fd, &e->rect);
	if (node->state != _PLINE)
		draw_bin_part(node, e, fd, node_id);
	else
		draw_pline_part(node, e, fd, node_id);
	return (node_id);
}
