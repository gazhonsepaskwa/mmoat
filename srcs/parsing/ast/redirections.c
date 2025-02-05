/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:38:26 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/05 07:38:26 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_redir	get_redir(t_node *node)
{
	if (!node)
		return (_NR);
	else if (!ft_strncmp(node->val, ">>", 2))
		return (_RED_DR);
	else if (!ft_strncmp(node->val, ">", 1))
		return (_RED_R);
	else if (!ft_strncmp(node->val, "<<", 2))
		return (_RED_DL);
	else if (!ft_strncmp(node->val, "<", 1))
		return (_RED_L);
	return (_NR);
}

static void	add_redir(t_redir redir, t_redir **redir_list)
{
    int     i;
    int     j;
    t_redir *tmp;

    i = 0;
    while ((*redir_list)[i] != _NR)
        i++;
    tmp = ft_calloc(i + 2, sizeof(t_redir));
    j = -1;
    while ((*redir_list)[++j] != _NR)
        tmp[j] = (*redir_list)[j];
    tmp[j++] = redir;
    tmp[j] = _NR;
    free(*redir_list);
    *redir_list = tmp;
}

void	create_redir(t_node *cpy, t_ast_n *self)
{
	t_redir redir;

	while (cpy)
	{
		while (cpy && get_redir(cpy) == _NR)
			cpy = cpy->next;
		if (!cpy)
			break;
		redir = get_redir(cpy);
		add_redir(redir, &self->redir);
		add_to_tab(&self->files, cpy->next->val);
		cpy = cpy->next;
		while (cpy && cpy->next && get_redir(cpy) == _NR)
		{
			cpy = cpy->next;
		}
	}
}
