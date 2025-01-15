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

/*void truncate_after_exit_word(char **lst)*/
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
/*		if (truncate_mode)*/
/*		{*/
/*			free(lst[i]);*/
/*			lst[i] = NULL;*/
/*		}*/
/*		else*/
/*		{*/
/*			if (lst[i][0] == '(')*/
/*				depth += 1;*/
/*			if (lst[i][ft_strlen(lst[i]) - 1] == ')')*/
/*				depth -= 1;*/
/*			if (!ft_strncmp(lst[i], "exit", 4) && depth == 0)*/
/*				truncate_mode = TRUE;*/
/*		}*/
/*		i++;*/
/*	}*/
/*}*/

/*void print_tab(char **lst)*/
/*{*/
/*	int i = 0;*/
/*	while (lst[i])*/
/*	{*/
/*		printf("%s\n", lst[i]);*/
/*		i++;*/
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
		/*truncate_after_exit_word(lst);*/
		/*free_tab(lst);*/
		lst = tokenize(str);
		print_linked_list(lst);
	}
}
