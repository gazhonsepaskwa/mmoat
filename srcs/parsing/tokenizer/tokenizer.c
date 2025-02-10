/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:57 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:26:04 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_node	*tokenize_base(char *str)
{
	int		i;
	t_node	*head;
	char	**tab;

	tab = ft_split_keep(str, " \t\n");
	if (!tab)
		return (NULL);
	head = NULL;
	i = 0;
	while (tab[i])
	{
		if (!add_node_back(&head, tab[i], 0, 0))
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
	t_pres	last_pres;

	it = head;
	last_token = UNSET;
	last_pres = UNDEFINED;
	while (it != NULL)
	{
		it->token = get_token(it->val);
		it->pressision = get_pressision(it->val, it->token, last_token,
				last_pres);
		last_token = it->token;
		last_pres = it->pressision;
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
				first_str = copy_meta(it->val, &copied);
			else
				first_str = copy_unmeta(it->val, &copied);
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
		if (ft_strchr(it->val, q))
		{
			while (it->next && !ft_strchr(it->next->val, q))
				if (!merge_with_next_node(it))
					return (0);
			if (it->next && !merge_with_next_node(it))
				return (0);
		}
		it = it->next;
	}
	return (1);
}

void debug_token_list(t_node* lst, char *msg)
{
	t_node *cpy;

	cpy = lst;
	if (DEBUG)
	{
		ft_debug("==================================================================={%s}\n", msg);
		while (cpy)
		{
			ft_fprintf(2, "| %10s | TOKEN : %3d | PRESSISION : %3d |\n", cpy->val, cpy->token, cpy->pressision);
			cpy = cpy->next;
		}
		ft_debug("===================================================================\n\n");
	}
}

void	del_void_nodes(t_node **head)
{
	t_node *cpy;
	t_node *tmp;

	cpy = *head;
	if (ft_strlen((*head)->val) == 0)
	{
		cpy = (*head)->next;
		free ((*head)->val);
		free (*head);
	}
	*head = cpy; 
	while (cpy)
	{
		if (cpy->next && ft_strlen(cpy->next->val) == 0)
		{
			tmp = cpy->next->next;
			free(cpy->next->val);
			free(cpy->next);
			cpy->next = tmp;
		}
		cpy = cpy->next;
	}
}

t_node	*tokenize(char *str)
{
	t_node	*head;

	head = tokenize_base(str);
	if (!head)
		return (NULL);
	debug_token_list(head, "tokenize_base");
	if (!trim_nodes(head))
		return (NULL);
	debug_token_list(head, "trim_nodes");
	if (!unstick_nodes(head))
		return (NULL);
	debug_token_list(head, "unstick_nodes");
	stick_quote_node(head, 39);
	stick_quote_node(head, '"');
	debug_token_list(head, "stick quote node");
	if (!trim_nodes(head))
		return (NULL);
	debug_token_list(head, "trim_nodes");
	set_token(head);
	del_void_nodes(&head);
	debug_token_list(head, "tokenizer");
	if (syntax_error(head))
		return (NULL);
	return (head);
}
