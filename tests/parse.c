/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41  by nalebrun         #+#    #+#             */
/*   Updated: 2025/01/15 08:23:41  by nalebrun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

/*str_equal(char *original)*/
/*{*/
/**/
/*}*/

/*void truncate_after_exit_word(char *str)*/
/*{*/
/*	int	i;*/
/*	int	depth;*/
/*	int truncate_mode;*/
/**/
/*	i = 0;*/
/*	depth = 0;*/
/*	truncate_mode = FALSE;*/
/*	while (lst[i])*/
/*	{*/
/**/
/*	}*/
/*}*/

void print_linked_list(t_node *head) {
    t_node *current = head;
    while (current != NULL) {
        printf("Node - Priority: %d, Depth: %d, TOKEN: |%s|\n", current->priority, current->depth, current->token);
        current = current->next; // Move to the next node
    }
}

int main (int ac, char **av)
{
	(void)ac;

	char *str = ft_strtrim(av[1], " ");
	t_node *lst;

	if (str)
	{
		/*truncate_after_exit_word(str);*/
		lst = tokenize(str);
		print_linked_list(lst);
	}
}
