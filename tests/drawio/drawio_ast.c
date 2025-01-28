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
	rect->h = 150;
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

const char *translate_redir(t_redir redir)
{
	const char	*out;

	if (redir == _RED_L)
		out = "redir : < &#10;";
	else if (redir == _RED_R)
		out = "redir : > &#10;";
	else if (redir == _RED_DR)
		out = "redir : >> &#10;";
	else
		out = "Not redirected &#10;";
	return (out);
}

char *get_node_txt(t_ast_n *node)
{
    const char *st;
	char *out;
	char *cmd;
	char *args;
	const char *redir;
	char *inf;
	char *outf;

    st = translate_state(node->state);
	if (node->state == _CMD)
	{
		cmd = ft_sprintf("%s%s%s", NL, node->cmd, NL);
		args = ft_sprintf("future args", NL);
    	redir = translate_redir(node->redir);
		inf = ft_sprintf("Infile : %s%s", node->infile, NL);
		outf = ft_sprintf("Outfile : %s%s", node->outfile, NL);
	}
	else
	{
		cmd = ft_calloc(1, 1);
		args = ft_calloc(1, 1);
		redir = "";
		inf = ft_calloc(1, 1);
		outf = ft_calloc(1, 1);
	}

	out = ft_sprintf("%s%s%s%s%s%s%s", st, cmd, args, NL, redir, inf, outf);
	free(cmd);
	free(args);
	free(inf);
	free(outf);
 	return (out);
}

int print_ast(t_ast_n *node, t_dio_elem *rect, t_dio_elem *arrow, int fd)
{
    int i;
	int node_id;

    if (!node || !rect)
        return -1;

    rect->text = get_node_txt(node);
    node_id = drawio_create_elem(fd, rect);
	
	if (node->state != _PLINE)
	{
		rect->y += rect->h + 50;
		arrow->id_dst = print_ast(node->left, rect, arrow, fd);
		arrow->id_src = node_id;
		drawio_create_elem(fd, arrow);

		rect->x += rect->w + 50;
		arrow->id_dst = print_ast(node->right, rect, arrow, fd);
		arrow->id_src = node_id;
		drawio_create_elem(fd, arrow);

		rect->y -= rect->h + 50;
		if (node->state == _CMD)
			rect->x -= rect->w + 50;
	}
	else
	{
		i = 0;
		rect->y += rect->h + 50;
		while (node->pline[i])
		{
			arrow->id_dst = print_ast(node->pline[i++], rect, arrow, fd);
			arrow->id_src = node_id;
			drawio_create_elem(fd, arrow);
			rect->x += rect->w + 50;
		}
	}
	return (node_id);
}
void	gen_dio_ast(t_ast_n *head, int fd)
{
	t_dio_elem	rect;
	t_dio_elem	arrow;

	set_ast_rect(&rect);
	arrow.type = ARROW;
	arrow.id_src = 0;
	arrow.id_dst = 0;
	
	print_ast(head, &rect, &arrow, fd);
	return ;
}
