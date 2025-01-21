/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:49 by  nalebrun         #+#    #+#             */
/*   Updated: 2025/01/20 13:15:03 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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

int	add_node_back(t_node *head, char *val, t_token token)
{
	if (!val)
		return (0);
	while (head->next != NULL)
		head = head->next;
	head->next = create_node(val, token);
	if (head->next == NULL)
		return (0);
	return (1);
}

void	free_linked_list(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->val);
		free(tmp);
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

// have to be deleted after
void	debug_linked_list(t_node *head, char *msg)
{
	t_node	*current;
	char	*token;
	char	*pres;

	current = head;
	printf("----------------------------------------------------------{%s} \n",
		msg);
	while (current != NULL)
	{
		// set val for base token
		if (current->token == OPERATOR)
			token = ft_strdup("OPERATOR");
		else if (current->token == WORD)
			token = ft_strdup("    WORD");
		else if (current->token == UNSET)
			token = ft_strdup("   UNSET");
		else
			token = ft_strdup("     ???");

		// set vals for pressision token
		if (current->pressision == COMMAND)
			pres = ft_strdup("COMMAND");
		else if (current->pressision == UNDEFINED)
			pres = ft_strdup("UNDEF  ");
		else if (current->pressision == AND)
			pres = ft_strdup("AND    ");
		else if (current->pressision == OR)
			pres = ft_strdup("OR     ");
		else if (current->pressision == PIPE)
			pres = ft_strdup("PIPE   ");
		else if (current->pressision == SUBSH_S)
			pres = ft_strdup("SUBSH_S");
		else if (current->pressision == SUBSH_E)
			pres = ft_strdup("SUBSH_E");
		else if (current->pressision == RED_L)
			pres = ft_strdup("RED_L  ");
		else if (current->pressision == RED_R)
			pres = ft_strdup("RED_R  ");
		else if (current->pressision == HEREDOC)
			pres = ft_strdup("HEREDOC");
		else if (current->pressision == D_RED_R)
			pres = ft_strdup("D_RED_R");
		else
			pres = ft_strdup("???    ");

		printf("| Node - TOKEN: %s.%s -> val: |%s|\n", token, pres, current->val);
		free(token);
		free(pres);
		current = current->next;
	}
	printf("----------------------------------------------------------\n\n");
}
