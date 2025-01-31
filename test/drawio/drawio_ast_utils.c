/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawio_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:21:09 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/29 09:21:09 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawio.h"

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

const char	*translate_redir(t_redir redir)
{
	const char	*out;

	if (redir == _RED_L)
		out = "redir : RED_L&#10;";
	else if (redir == _RED_R)
		out = "redir : RED_R&#10;";
	else if (redir == _RED_DR)
		out = "redir : _RED_DR &#10;";
	else
		out = "Not redirected &#10;";
	return (out);
}

t_dio_node	get_cmd_txt(t_ast_n *node)
{
	t_dio_node	txt;
	char		*args;

	txt.st = translate_state(node->state);
	if (node->state == _CMD)
	{
		txt.cmd = ft_sprintf("%s%s", NL, node->cmd);
		txt.cmd = replace_left_red(txt.cmd);
		args = ft_tabstr(node->args);
		txt.args = ft_sprintf("%s%s%s", NL, args, NL);
		free(args);
		txt.redir = translate_redir(node->redir);
		txt.inf = ft_sprintf("Infile : %s%s", node->infile, NL);
		txt.outf = ft_sprintf("Outfile : %s", node->outfile);
	}
	else
	{
		txt.cmd = ft_calloc(1, 1);
		txt.args = ft_calloc(1, 1);
		txt.redir = "";
		txt.inf = ft_calloc(1, 1);
		txt.outf = ft_calloc(1, 1);
	}
	return (txt);
}
