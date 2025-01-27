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
# include "../tokenizer/tokenizer.h"
# include "../ast/ast.h"

// internal
char* replace_ampercent(char *src);

// external
void 	gen_dio_linked_list(t_node *head, int fd);
void	gen_dio_ast(t_ast_n *head, int fd);
#endif
