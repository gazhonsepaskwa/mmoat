/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:49 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:27:00 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*create_node(char *val, t_token token)
{
	t_node	*node;

	if (!val)
		return (NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->val = ft_strdup(val);
	node->token = token;
	node->pressision = 0;
	node->next = NULL;
	return (node);
}

int	add_node_back(t_node **head, char *val, t_token token, t_pres pres)
{
	t_node	*tmp;

	if (!val)
		return (0);
	if (!head || !(*head))
	{
		*head = create_node(val, token);
		(*head)->pressision = pres;
		return (1);
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = create_node(val, token);
	tmp->next->pressision = pres;
	if (tmp->next == NULL)
		return (0);
	return (1);
}

void	free_linked_list(t_node *head)
{
	t_node	*tmp;
	t_node	*next;

	tmp = head;
	while (tmp)
	{
		next = tmp->next;
		ft_free(&tmp->val);
		free(tmp);
		tmp = next;
	}
}

int	create_node_after(t_node *elem, char *val)
{
	t_node	*tmp_next;

	tmp_next = elem->next;
	elem->next = create_node(val, 0);
	if (!elem->next)
		return (0);
	elem->next->next = tmp_next;
	return (1);
}

int	merge_with_next_node(t_node *node)
{
	char	*tmp_val;
	t_node	*tmp_next;

	tmp_val = ft_strjoin(node->val, node->next->val);
	if (!tmp_val)
		return (0);
	ft_free(&node->val);
	node->val = tmp_val;
	ft_free(&node->next->val);
	tmp_next = node->next->next;
	free(node->next);
	node->next = tmp_next;
	return (1);
}
