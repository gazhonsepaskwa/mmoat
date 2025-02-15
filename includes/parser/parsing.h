/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:28 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:45:11 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_node	t_node;
typedef struct s_ast_n	t_ast_n;
typedef struct s_msh	t_msh;

t_ast_n	*parser(char *input, t_msh *msh);

void	interpret_cmd(char **input, t_msh *msh);

int		unexpected_token(t_node *node);
int		is_aop_operator(t_node *node);
int		is_redir(t_node *cpy);
int		is_basic_word(t_node *cpy);
int		syntax_err_mess(char *token_base, int selected);
int		check_unclosed(char *c, t_node *node);
int		check_unclosed_quote(char *c, t_node *node);

int		last_tok_redir(t_node *lst);
int		last_tok_subsh(t_node *lst);

#endif
