/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:57 by  nalebrun         #+#    #+#             */
/*   Updated: 2025/01/20 13:15:25 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_node	*tokenize_base(char *str)
{
	int		i;
	t_node	*head;
	char	**tab;

	tab = ft_split_keep(str, " \t\n");
	if (!tab)
		return (NULL);
	head = create_node(tab[0], 0);
	if (!head)
		return (free(tab), NULL);
	i = 1;
	while (tab[i])
	{
		if (!add_node_back(head, tab[i], 0))
			return (free(tab), NULL);
		i++;
	}
	free_tab(tab);
	return (head);
}

static void	set_token(t_node *head)
{
	t_node	*it;
	t_token	last_token;

	it = head;
	last_token = UNSET;
	while (it != NULL)
	{
		it->token = get_token(it->val);
		it->pressision = get_pressision(it->val, it->token, last_token);
		last_token = it->token;
		it = it->next;
	}
}

static int	unstick_nodes(t_node *head)
{
	t_node	*it;
	char	*first_str;
	char	*second_str;
	int		copied;

	it = head;
	while (it != NULL)
	{
		if (is_sticked(it->val))
		{
			if (is_meta(it->val[0]))
				first_str = copy_meta_xor(it->val, &copied, 0);
			else
				first_str = copy_meta_xor(it->val, &copied, 1);
			second_str = ft_substr(it->val, copied, ft_strlen(it->val)
					- copied);
			ft_free(&it->val);
			it->val = ft_strdup(first_str);
			create_node_after(it, second_str);
			ft_free(&first_str);
			ft_free(&second_str);
		}
		it = it->next;
	}
	return (1);
}

static int	stick_quote_node(t_node *head, char q)
{
	t_node	*it;

	it = head;
	while (it != NULL)
	{
		if (it->val[0] == q && !ft_strchr(&it->val[1], q)
			&& find_quote_node(it->next, q))
		{
			while (it->next->val[0] != q)
				if (!merge_with_next_node(it))
					return (0);
			if (!merge_with_next_node(it))
				return (0);
		}
		it = it->next;
	}
	return (1);
}

t_node	*tokenize(char *str)
{
	t_node	*head;

	head = tokenize_base(str);
	if (!head)
		return (NULL);
	debug_linked_list(head, "Base_cut");
	if (!trim_nodes(head))
		return (NULL);
	debug_linked_list(head, "Trimed");
	if (!unstick_nodes(head))
		return (NULL);
	debug_linked_list(head, "Nodes Unsticked");
	stick_quote_node(head, 39);
	stick_quote_node(head, '"');
	debug_linked_list(head, "Quote Sticked");
	set_token(head);
	return (head);
}
