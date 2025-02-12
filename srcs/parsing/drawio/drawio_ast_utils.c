/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:21:09 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 18:02:51 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

const char	*translate_state(t_state state)
{
	const char	*out;

	if (state == _AND)
		out = "CMD_AND";
	else if (state == _OR)
		out = "CMD_OR";
	else if (state == _PLINE)
		out = "CMD_PIPELINE";
	else if (state == _CMD)
		out = "SIMPLE_CMD";
	else if (state == _SUBSH)
		out = "SUBSHELL";
	else
		out = "UNDEFINED";
	return (out);
}

static void	else_case(t_dio_node *txt)
{
	txt->cmd = ft_calloc(1, 1);
	txt->args = ft_calloc(1, 1);
	txt->files = ft_calloc(1, 1);
}

t_dio_node	get_cmd_txt(t_ast_n *node)
{
	t_dio_node	txt;
	char		*args;

	txt.st = translate_state(node->state);
	if (node->state == _CMD)
	{
		if (node->cmd)
			txt.cmd = ft_sprintf("%s%s", NL, node->cmd);
		else
			txt.cmd = ft_strdup(NL);
		txt.cmd = replace_left_red(txt.cmd);
		if (node->args && node->args[0])
			args = ft_tabstr(node->args);
		else
			args = ft_strdup("");
		txt.args = ft_sprintf("%s%s%s", NL, args, NL);
		free(args);
		txt.files = ft_sprintf("redir: UNCHECKED\n");
	}
	else
		else_case(&txt);
	return (txt);
}
