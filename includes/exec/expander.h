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

# include <sys/types.h>
# include <dirent.h>

typedef struct s_ast_n	t_ast_n;

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

//EXPANDER_VAR_UTILS
int		expand_exit(t_ast_n *node, int j, int k);
int		get_new_len(t_ast_n *node, int j);
int		valid_expand(t_ast_n *node, int j, int k);
char	*create_new(t_ast_n *node, int j, int *len);
void	handle_copy(t_ast_n *node, int j, char **new);
void	cat_exit(t_ast_n *node, char **new, int *i, int *k);

#endif
