/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:57 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:30 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_node	*tokenize_base(char *str)
{
	t_node	*lst;
	char	*tmp;
	int		i;
	int		len;

	lst = NULL;
	tmp = NULL;
	i = 0;
	while (str[i])
	{
		len = goto_nxt_space(&(str[i]));
		tmp = ft_substr(&str[i], 0, len);
		add_node_back(&lst, tmp, 0, 0);
		ft_free(&tmp);
		i += len;
	}
	return (lst);
}

void unstick_main(t_node *it)
{
	char	*first_str;
	char	*second_str;
	int		copied;

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

bool	unstick_quote(int count, t_node *it)
{
	char	*first_str;
	char	*second_str;

	if (count == 0)
		return (false);
	first_str = ft_substr(it->val, 0, count + 1);
	second_str = ft_substr(it->val, count + 1, ft_strlen(it->val));
	ft_free(&it->val);
	it->val = ft_strdup(first_str);
	create_node_after(it, second_str);
	ft_free(&first_str);
	ft_free(&second_str);
	return (true);
}

int	quote_sticked(char *str)
{
	int 	i;
	char	quote;

	i = 1;
	quote = 0;
	update_quote(&quote, str[0]);
	while (str[i])
	{
		if (quote && str[i] == quote)
			if (str[i + 1] && is_meta(str[i + 1]))
				return(i);
		update_quote(&quote, str[i]);
		i++;
	}
	return (0);
}

static int	unstick_nodes(t_node *head)
{
	t_node	*it;

	it = head;
	while (it != NULL)
	{
		if (unstick_quote(quote_sticked(it->val), it))
			break ;
		if (is_sticked(it->val))
			unstick_main(it);
		it = it->next;
	}
	return (1);
}

static void	del_void_nodes(t_node **head)
{
	t_node	*cpy;
	t_node	*tmp;

	cpy = *head;
	if (ft_strlen((*head)->val) == 0)
	{
		cpy = (*head)->next;
		free((*head)->val);
		free(*head);
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
	debug_token_list(head, "base");
	if (!trim_nodes(head))
		return (NULL);
	debug_token_list(head, "trim");
	del_void_nodes(&head);
	debug_token_list(head, "del void");
	unstick_nodes(head);
	debug_token_list(head, "unstick");
	del_void_nodes(&head);
	debug_token_list(head, "del void");
	set_token(head);
	debug_token_list(head, "set token");
	if (syntax_error(head))
		return (free_linked_list(head), NULL);
	return (head);
}
