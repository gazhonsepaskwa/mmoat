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

void truncate_comment(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '#')
		{
			str[i] = 0;
			return ;
		}
		i++;
	}
}


int main (int ac, char **av)
{
	(void)ac;

	t_node *lst;

	truncate_comment(av[1]);
	lst = tokenize(av[1]);
	if (!lst)
		return (1);
	// debug_linked_list(lst);
	free_linked_list(lst);
	// free la list wesh
}
