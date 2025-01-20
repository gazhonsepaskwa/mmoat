/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:30:12 by  nalebrun         #+#    #+#             */
/*   Updated: 2025/01/20 13:15:34 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../includes/minishell.h"

typedef enum e_token
{
	UNSET,
	OPERATOR,
	WORD
}					t_token;

typedef enum e_pres
{
	AND,
	OR,
	PIPE,
	SUBSH_S,
	SUBSH_E
}					t_pres;

typedef struct s_node
{
	struct s_node	*next;
	char			*val;
	enum e_token	token;
	enum e_pres		pressision;
}					t_node;

t_node				*tokenize(char *str);
t_node				*create_node(char *val, t_token token);
int					add_node_back(t_node *head, char *val, t_token token);
int					merge_with_next_node(t_node *node);
void				free_linked_list(t_node *stack);
t_token				get_token(char *str);
int					create_node_after(t_node *elem, char *val);
char				*copy_meta_xor(char *val, int *copied, int rev);
int					is_meta(char c);
int					is_sticked(char *val);

void				debug_linked_list(t_node *head, char *msg);

#endif
