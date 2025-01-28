/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 09:34:41 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 09:34:41 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_DRAWIO_H
# define LIB_DRAWIO_H

# include "../../libft.h" 

# define NL "&#10;"

typedef enum e_dio_elemtype
{
	RECT,
	ARROW,
}	t_dio_elemtype;

typedef struct s_dio_elem
{
	t_dio_elemtype	type;
	char			*text;
	int				x;
	int				y;
	int				w;
	int				h;
	int				id_src;
	int				id_dst;
	int				rounded;

}	t_dio_elem;

int		drawio_init(char *file_path);
int		drawio_create_elem(int fd, t_dio_elem *elem);
void	drawio_end_file(int fd);

#endif
