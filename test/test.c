/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/31 13:40:10 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	truncate_comment(char *str)
{
	int		i;
	char	inquote;

	if (!str)
		return ;
	i = 0;
	inquote = 0;
	while (str[i])
	{
		if (!inquote && (str[i] == 39 || str[i] == '"'))
			inquote = str[i];
		else if (inquote && (str[i] == inquote))
			inquote = 0;
		if (str[i] == '#' && !inquote && str[i - 1] && str[i - 1] != '\\')
		{
			str[i] = 0;
			return ;
		}
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_node	*lst;
	// t_ast_n	*ast;
	int 	dio;
	(void)envp;

	if (ac != 3)
	{
		ft_error("./test drawio_file command_str\n");
		return (1);
	}
	truncate_comment(av[1]);
	lst = tokenize(av[2]);
	if (!lst)
		return (1);
	if (DEBUG)
	{
		dio = drawio_init(av[1]);
		// gen_dio_linked_list(lst, dio);
	}
	// ast = get_ast(envp, lst);
	// if (!ast)
		// return (1);
	

	// tmp
	t_nodell *lls = cutll(lst, "||", -1);
	while (lls)
	{
		gen_dio_linked_list(lls->node, dio);
		lls = lls->next;
	}
	if (DEBUG)
	{
		// gen_dio_ast(ast, dio);
		drawio_end_file(dio);
		ft_debug(" draw.io file generated !\n");
	}
	free_linked_list(lst);
}
