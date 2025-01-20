/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41 by  nalebrun         #+#    #+#             */
/*   Updated: 2025/01/20 13:15:47 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"

void	truncate_comment(char *str)
{
	int	i;

	if (!str)
		return ;
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

int	main(int ac, char **av)
{
	t_node	*lst;
	char	*expanded;

	(void)ac;
	truncate_comment(av[1]);
	expanded = expander(av[1]);
	lst = tokenize(expanded);
	if (!lst)
		return (free(expanded), 1);
	ft_free(expanded);
	debug_linked_list(lst, "Tokenized");
	free_linked_list(lst);
}
