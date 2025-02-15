/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:59:43 by nalebrun         ###   ########.fr       */
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

static void	debug_dio_ast(t_ast_n *ast, int dio)
{
	if (DEBUG)
	{
		gen_dio_ast(ast, dio);
		drawio_end_file(dio);
	}
}

t_ast_n	*parser(char *input, t_msh *msh)
{
	t_node	*lst;
	t_ast_n	*ast;
	int		dio;

	dio = 0;
	truncate_comment(input);
	lst = tokenize(input);
	if (!lst)
	{
		msh->ex_code = 2;
		return (NULL);
	}
	create_heredoc(lst, msh);
	if (DEBUG)
		dio = drawio_init(DIO_PATH);
	// gen_dio_linked_list(lst, dio);
	ast = get_ast(msh, lst);
	debug_dio_ast(ast, dio);
	if (!ast)
		return (NULL);
	free_linked_list(lst);
	return (ast);
}
