/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:42:28 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/10 13:42:28 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H


typedef struct s_node	t_node;
typedef struct s_msh	t_msh;

void	read_hereinput(char *limiter, t_node *lst, t_msh *msh);
void	parse_heredoc(char *limiter, t_node *lst, t_msh *msh);
void	create_heredoc(t_node *lst, t_msh *msh);

#endif
