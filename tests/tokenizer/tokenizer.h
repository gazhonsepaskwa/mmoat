/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:30:12  by nalebrun         #+#    #+#             */
/*   Updated: 2025/01/15 13:30:12  by nalebrun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H 
# define TOKENIZER_H

# include "../includes/minishell.h"

typedef struct s_node
{
	struct s_node	*next;
	char			*token;
	int				priority;
	int				depth;
}					t_node;

t_node	*tokenize(char *str);
t_node	*create_node(char *token, int priority, int depth);
void	add_node_back(t_node* head, int depth, char *token);
void	ajust_depth(int *depth, char c);
int		get_priority(char *token);

#endif
