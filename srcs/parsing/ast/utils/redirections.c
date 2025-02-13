/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:38:26 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:57:42 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

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
	int		i;
	int		j;
	t_redir	*tmp;

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

void	create_redir(t_node *head, t_ast_n *self)
{
	t_redir	redir;

	while (head)
	{
		while (head && get_redir(head) == _NR)
			head = head->next;
		if (!head)
			break ;
		redir = get_redir(head);
		add_redir(redir, &self->redir);
		add_to_tab(&self->files, head->next->val);
		head = head->next;
		while (head && head->next && get_redir(head) == _NR)
			head = head->next;
	}
}

int	in_parenthesis(t_node *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->pressision == SUBSH_S)
			count += 1;
		if (head->pressision == SUBSH_E)
			count -= 1;
		head = head->next;
	}
	if (count != 0)
		return (1);
	return (0);
}

void	create_redir_subsh(t_node *head, t_ast_n *self)
{
	t_redir	redir;

	while (head)
	{
		while (head && (get_redir(head) == _NR || in_parenthesis(head)))
			head = head->next;
		if (!head)
			break ;
		redir = get_redir(head);
		add_redir(redir, &self->redir);
		add_to_tab(&self->files, head->next->val);
		head = head->next;
		while (head && head->next && get_redir(head) == _NR)
			head = head->next;
	}
}
