/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:08:53 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:12 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <string.h>

static int	parenthesis_error(t_node *cpy)
{
	if (!ft_strncmp(cpy->val, "(", 1) && cpy->next
		&& !ft_strncmp(cpy->next->val, ")", 1))
		return (syntax_err_mess(cpy->next->val, 0));
	if (!ft_strncmp(cpy->val, ")", 1) && cpy->next
		&& !ft_strncmp(cpy->next->val, "(", 1))
		return (syntax_err_mess(cpy->next->val, 0));
	if (is_aop_operator(cpy) && cpy->next
		&& !ft_strncmp(cpy->next->val, ")", 1))
		return (syntax_err_mess(cpy->next->val, 0));
	if (cpy->next && !ft_strncmp(cpy->next->val, "(", 1)
		&& !is_aop_operator(cpy))
		return (syntax_err_mess(cpy->next->val, 0));
	return (0);
}

static int	redir_error(t_node *cpy)
{
	if (is_redir(cpy) && !cpy->next)
		return (syntax_err_mess(cpy->val, 3));
	if (is_redir(cpy) && cpy->next && !is_basic_word(cpy->next))
		return (syntax_err_mess(cpy->next->val, 0));
	if (is_redir(cpy) && cpy->next && cpy->next->next
		&& !ft_strncmp(cpy->next->next->val, "(", 1))
		return (syntax_err_mess(cpy->next->next->val, 0));
	return (0);
}

static int	aop_error(t_node *cpy)
{
	if (!is_aop_operator(cpy))
		return (0);
	if (cpy->next == NULL)
		return (syntax_err_mess(cpy->val, 3));
	if (is_aop_operator(cpy->next))
		return (syntax_err_mess(cpy->next->val, 0));
	if (ft_strlen(cpy->val) > 2)
		return (syntax_err_mess(cpy->val, 0));
	return (0);
}

int	unclosed(t_node *head)
{
	if (check_unclosed("()", head) != 0)
		return (syntax_err_mess("()", check_unclosed("()", head)));
	if (check_unclosed_quote("\"", head) != 0)
		return (syntax_err_mess("\"\"", 1));
	if (check_unclosed_quote("'", head) != 0)
		return (syntax_err_mess("'", 1));
	return (0);
}

int	syntax_error(t_node *head)
{
	t_node	*cpy;

	cpy = head;
	if (is_aop_operator(cpy) && cpy->next == NULL)
		return (syntax_err_mess(cpy->val, 0));
	while (cpy)
	{
		if (redir_error(cpy) || parenthesis_error(cpy) || aop_error(cpy))
			return (1);
		if (unexpected_token(cpy))
			return (syntax_err_mess(cpy->val, 0));
		cpy = cpy->next;
	}
	if (unclosed(head))
		return (1);
	return (0);
}
