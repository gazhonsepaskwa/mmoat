/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:26 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/14 10:59:00 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include <string.h>

static void	skip_parentheses(t_node **lst)
{
	if (!ft_strncmp((*lst)->val, "(", 1))
	{
		(*lst) = (*lst)->next;
		while (*lst && ft_strncmp((*lst)->val, ")", 1))
		{
			if (!ft_strncmp((*lst)->val, "(", 1))
				skip_parentheses(lst);
			else
				(*lst) = (*lst)->next;
		}
		if (*lst)
			(*lst) = (*lst)->next;
	}
}

static t_node	*find_token(char *tok, t_node *lst)
{
	while (lst)
	{
		skip_parentheses(&lst);
		if (lst && !ft_strncmp(lst->val, tok, ft_strlen(tok)))
			return (lst);
		if (lst)
			lst = lst->next;
	}
	return (NULL);
}

static t_node	*rfind_token(char *tok, t_node *lst)
{
	t_node	*lst_it;

	lst_it = NULL;
	while (lst)
	{
		skip_parentheses(&lst);
		if (lst && !ft_strncmp(lst->val, tok, ft_strlen(tok)))
			lst_it = lst;
		if (lst)
			lst = lst->next;
	}
	return (lst_it);
}

t_node	*get_top_token(t_node *lst, t_state *state)
{
	*state = _SUBSH;
	if (rfind_token("&&", lst) > rfind_token("||", lst))
	{
		*state = _AND;
		return (find_token("&&", lst));
	}
	else if (rfind_token("||", lst) > rfind_token("&&", lst))
	{
		*state = _OR;
		return (find_token("||", lst));
	}
	else if (find_token("|", lst))
	{
		*state = _PLINE;
		return (find_token("|", lst));
	}
	else if (!ft_strncmp(lst->val, "(", 1) && last_tok_redir(lst))
		return (lst);
	else if (!ft_strncmp(lst->val, "(", 1) && last_tok_subsh(lst))
		return (lst);
	else
	{
		*state = UNDEF;
		return (NULL);
	}
}
