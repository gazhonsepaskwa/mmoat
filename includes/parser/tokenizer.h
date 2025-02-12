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

typedef enum e_token
{
	UNSET,
	OPERATOR,
	WORD
}					t_token;

typedef enum e_pres
{
	UNDEFINED,
	COMMAND,
	AND,
	OR,
	PIPE,
	SUBSH_S,
	SUBSH_E,
	RED_L,
	RED_R,
	HEREDOC,
	D_RED_R,
	PARAMETER,
	RED_FILE,
	LIM
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
int					add_node_back(t_node **head, char *val, t_token token, t_pres pres);
int					merge_with_next_node(t_node *node);
void				free_linked_list(t_node *stack);
t_token				get_token(char *str);
t_pres				get_pressision(char *s, t_token token, t_token last_token, t_pres last_pres);
int					create_node_after(t_node *elem, char *val);
int					is_meta(char c);
int					is_sticked(char *val);
int					trim_nodes(t_node *head);
void				debug_linked_list(t_node *head, char *msg);
int					find_quote_node(t_node *head, char q);
int					syntax_error(t_node *head);
char				*copy_meta(char *val, int *copied);
char				*copy_unmeta(char *val, int *copied);
void				debug_token_list(t_node* lst, char *msg);
void				set_token(t_node *head);

#endif
