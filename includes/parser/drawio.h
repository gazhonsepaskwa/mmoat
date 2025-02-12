/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:20:35 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/27 14:20:35 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWIO_H
# define DRAWIO_H

# include "../../lib/libft/libft.h"

typedef struct s_ast_n	t_ast_n;
typedef struct s_node	t_node;

typedef struct s_dio_node
{
	const char	*st;
	char		*cmd;
	char		*args;
	char		*files;
}			t_dio_node;

typedef struct s_elems
{
	t_dio_elem	rect;
	t_dio_elem	arrow;
}				t_elems;

// internal
char		    *replace_ampercent(char *src);
char		    *replace_left_red(char *src);
t_dio_node	get_cmd_txt(t_ast_n *node);
int			    print_ast(t_ast_n *node, t_elems *e, int fd);

// external
void		    gen_dio_linked_list(t_node *head, int fd);
void        gen_dio_ast(t_ast_n *head, int fd);
#endif
