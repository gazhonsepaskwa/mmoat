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

# include "../minishell.h"

void	read_hereinput(char *limiter);
void	parse_heredoc(char *limiter);
void	create_heredoc(t_node *lst);

#endif
