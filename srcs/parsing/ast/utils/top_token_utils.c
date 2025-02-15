/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:28:47 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/15 13:31:44 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	last_tok_subsh(t_node *lst)
{
	while (lst)
	{
		if ((lst->next == NULL) && !ft_strncmp(lst->val, ")", 1))
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	last_tok_redir(t_node *lst)
{
	while (lst)
	{
		if ((lst->next == NULL || lst->next->pressision == D_RED_R
				|| lst->next->pressision == RED_R
				|| lst->next->pressision == RED_L
				|| lst->next->pressision == HEREDOC) && !ft_strncmp(lst->val,
				")", 1))
			return (1);
		lst = lst->next;
	}
	return (0);
}
