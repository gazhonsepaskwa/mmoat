/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:47:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 10:45:02 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib_drawio.h"
#include "../header/dio_private.h"

int	drawio_init(char *file_path)
{
	int	fd;

	fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	ft_fprintf(fd, "<mxfile host=\"app.diagrams.net\" ");
	ft_fprintf(fd, "modified=\"2025-01-24T12:00:00Z\" ");
	ft_fprintf(fd, "agent=\"c_generator\" version=\"15.8.7\" ");
	ft_fprintf(fd, "type=\"device\">\n");
	ft_fprintf(fd, "<diagram id=\"GEN\" name=\"GEN-Diagram\">\n");
	ft_fprintf(fd, "<mxGraphModel>\n");
	ft_fprintf(fd, "<root>\n");
	ft_fprintf(fd, "<mxCell id=\"0\"/>\n");
	ft_fprintf(fd, "<mxCell id=\"1\" parent=\"0\"/>\n");
	return (fd);
}

void	drawio_end_file(int fd)
{
	ft_fprintf(fd, "</root>\n</mxGraphModel>\n</diagram>\n</mxfile>");
	close(fd);
}

int	drawio_create_elem(int fd, t_dio_elem *elem)
{
	static int	id = 1;

	id ++;
	if (elem->type == ARROW)
		return (draw_arrow(fd, id, elem));
	if (elem->type == RECT || elem->type)
		return (draw_rect(fd, id, elem));
	return (0);
}
