/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:48:37 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 12:17:10 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**lltotab(t_node *lst, t_node *limiter)
{
	char	**out;
	int		count;
	t_node	*cpy;

	count = 0;
	cpy = lst;
	while (cpy && cpy != limiter)
	{
		count++;
		cpy = cpy->next;
	}
	out = ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	cpy = lst;
	count = 0;
	while (cpy && cpy != limiter)
	{
		out[count] = ft_strdup(cpy->val);
		count++;
		cpy = cpy->next;
	}
	out[count] = NULL;
	return (out);
}

char	**get_args(t_node *start)
{
	t_node	*cpy;
	char	**out;

	cpy = NULL;
	while (start)
	{
		while (start && get_redir(start))
			start = start->next->next;
		if (start)
		{
			add_node_back(&cpy, start->val, start->token, start->pressision);
			start = start->next;
		}
	}
	out = lltotab(cpy, NULL);
	free_linked_list(cpy);
	return (out);
}

void	create_cmd(t_ast_n *self, t_node *lst)
{
	char	**cmd_args;
	int		i;

	self->state = _CMD;
	self->files = NULL;
	self->redir = ft_calloc(1, sizeof(t_redir));
	self->redir[0] = _NR;
	cmd_args = get_args(lst);
	self->args = cmd_args;
	self->cmd = NULL;
	if (cmd_args && cmd_args[0])
		self->cmd = ft_strdup(cmd_args[0]);
	create_redir(lst, self);
	if (DEBUG)
	{
		i = -1;
		ft_debug("==== CMD REDIR\n");
		while (self->files && self->files[++i])
			ft_debug("redi : [%d]%s\n", self->redir[i], self->files[i]);
		ft_debug("==== CMD ARGS\n");
		i = -1;
		while (self->args && self->args[++i])
			ft_debug("args : %s\n", self->args[i], self->args[i]);
		ft_debug("==== CMD DONE\n\n");
	}
}
