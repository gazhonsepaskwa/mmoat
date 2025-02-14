/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:00:49 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:22 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_aop_operator(t_node *node)
{
	if (!node || node->token != OPERATOR)
		return (0);
	if (node->pressision == AND || node->pressision == OR
		|| node->pressision == PIPE)
		return (1);
	return (0);
}

int	unexpected_token(t_node *node)
{
	if ((!ft_strncmp(node->val, "&", 1) && ft_strncmp(node->val, "&&", 2))
		|| !ft_strncmp(node->val, ";", 1) || !ft_strncmp(node->val, "[", 1)
		|| !ft_strncmp(node->val, "]", 1) || !ft_strncmp(node->val, "{", 1)
		|| !ft_strncmp(node->val, "}", 1))
		return (1);
	return (0);
}

int	is_redir(t_node *cpy)
{
	if (cpy->pressision == RED_L
		|| cpy->pressision == RED_R
		|| cpy->pressision == HEREDOC
		|| cpy->pressision == D_RED_R)
		return (1);
	return (0);
}

int	is_basic_word(t_node *cpy)
{
	if (is_aop_operator(cpy)
		|| is_redir(cpy)
		|| !ft_strncmp(cpy->val, ")", 1)
		|| !ft_strncmp(cpy->val, "(", 1))
		return (0);
	return (1);
}
