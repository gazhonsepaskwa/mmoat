/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:06:11 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 10:06:11 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../drawio.h"
#include "../header/dio_private.h"

int	draw_rect(int fd, int id, t_dio_elem *elem)
{
	ft_fprintf(fd, "<mxCell id=\"%d\" ", id);
	ft_fprintf(fd, "value=\"%s\" ", elem->text);
	ft_fprintf(fd, "style=\"rounded=%d;whiteSpace=wrap;", elem->rounded);
	ft_fprintf(fd, "html=1;\" vertex=\"1\" parent=\"1\"> \n");
	ft_fprintf(fd, "<mxGeometry x=\"%d\" y=\"%d\" ", elem->x, elem->y);
	ft_fprintf(fd, "width=\"%d\" height=\"%d\" ", elem->w, elem->h);
	ft_fprintf(fd, "as=\"geometry\"/>\n");
	ft_fprintf(fd, "</mxCell>\n");
	return (id);
}

int	draw_arrow(int fd, int id, t_dio_elem *elem)
{
	if (!elem->id_src || !elem->id_dst)
		return (0);
	ft_fprintf(fd, "<mxCell id=\"%d\" ", id);
	ft_fprintf(fd, "edge=\"1\" parent=\"1\" source=");
	ft_fprintf(fd, "\"%d\" target=\"%d\">\n", elem->id_src, elem->id_dst);
	ft_fprintf(fd, "<mxGeometry relative=\"1\" as=\"geometry\"/>\n</mxCell>\n");
	return (id);
}
