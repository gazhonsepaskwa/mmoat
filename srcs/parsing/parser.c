/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 12:08:40 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_ast_n *parser(char *input, t_msh *msh)
{
	t_node	*lst;
	t_ast_n	*ast;
	int 	dio;

	truncate_comment(input);
	lst = tokenize(input);
	if (!lst)
		return (NULL);
	if (syntax_error(lst))
		return (NULL);
	if (DEBUG)
	{
		dio = drawio_init("ast.xml");
		gen_dio_linked_list(lst, dio);
	}
	ast = get_ast(msh, lst);
	if (!ast)
		return (NULL);
	if (DEBUG)
	{
		gen_dio_ast(ast, dio);
		drawio_end_file(dio);
		ft_debug(" draw.io file generated !\n");
	}
	free_linked_list(lst);
	return (ast);
}
