/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:21:00 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 15:32:08 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../minishell.h"
# include <sys/types.h>
# include <dirent.h>

int		in_dquote(char *str, char *ch);
int		in_squote(char *str, char *ch);
int		expand_var(t_ast_n *node, int j);
int		expand_tilde(t_ast_n *node, int j);
int		expand_star(t_ast_n *node, int j);
t_ast_n	*expand_node(t_ast_n *node);

//UTILS
bool	ft_fnmatch(const char *str, const char *pat);
int		in_squote(char *str, char *ch);
int		in_dquote(char *str, char *ch);
int		is_exvalidchar(char c);
int		exvalid_next(char c);

#endif
