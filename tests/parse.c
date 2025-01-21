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
/*#include "../includes/env.h"*/

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

/*static t_data	*init_data(char **envp)*/
/*{*/
/*	t_data	*data;*/
/**/
/*	data = malloc (sizeof(t_data));*/
/*	data->env = init_env(envp);*/
/*	return (data);*/
/*}*/

int	main(int ac, char **av, char **envp)
{
	t_node	*lst;

	(void)ac;
	(void)envp;
	/*t_data data;*/

	/*data = init_data(envp);*/
	truncate_comment(av[1]);
	lst = tokenize(av[1]);
	if (!lst)
		return (1);
	debug_linked_list(lst, "Tokenized");
	free_linked_list(lst);
}
