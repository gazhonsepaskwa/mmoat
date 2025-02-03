/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:14:26 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/31 17:14:26 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	last_tok_subsh(t_node *lst)
{
	while (lst)
	{
		if (lst->next == NULL && !ft_strncmp(lst->val, ")", 1))
			return (1);
		lst = lst->next;
	}
	return (0);
}

static void	skip_parentheses(t_node **lst)
{
	if (!ft_strncmp((*lst)->val, "(", 1))
	{
		while ((*lst)->next && ft_strncmp((*lst)->next->val, ")", 1))
		{
			if (!ft_strncmp((*lst)->val, "(", 1))
				skip_parentheses(&(*lst)->next);
			*lst = (*lst)->next;
		}
	}
}

static t_node	*find_token(char *tok, t_node *lst)
{
	while (lst)
	{
		skip_parentheses(&lst);
		if (!ft_strncmp(lst->val, tok, ft_strlen(tok)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_node *get_top_token(t_node *lst, t_state *state)
{
	*state = _SUBSH;
	if (!ft_strncmp(lst->val, "(", 1) && last_tok_subsh(lst))
		return (lst);
	else if (find_token("&&", lst))
	{
		*state = _AND;
		return (find_token("&&", lst));
	}
	else if (find_token("||", lst))
	{
		*state = _OR;
		return (find_token("||", lst));
	}
	else if (find_token("|", lst))
	{
		*state = _PLINE;
		return (find_token("|", lst));
	}
	else
	{
		*state = UNDEF;
		return (NULL);
	}
}
