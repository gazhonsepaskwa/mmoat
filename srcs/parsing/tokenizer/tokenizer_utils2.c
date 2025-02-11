/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:10:17 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:33:26 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	debug_token_list(t_node *lst, char *msg)
{
	t_node	*cpy;

	cpy = lst;
	if (DEBUG)
	{
		ft_debug("====================================================\
==============={%s}\n",
			msg);
		while (cpy)
		{
			ft_fprintf(2, "| %10s | TOKEN : %3d | PRESSISION : %3d |\n",
				cpy->val, cpy->token, cpy->pressision);
			cpy = cpy->next;
		}
		ft_debug("====================================================\
===============\n\n");
	}
}

void	set_token(t_node *head)
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

int	find_quote_node(t_node *head, char q)
{
	t_node	*it;

	it = head;
	while (it != NULL)
	{
		if (it->val[0] == q)
			return (1);
		it = it->next;
	}
	return (0);
}
