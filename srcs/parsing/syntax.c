/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:08:53 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 12:08:53 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/parsing.h"

int only_operator(t_node *head)
{
	if (!head->next && head->token == OPERATOR)
		return (1);
	return (0);
}

int syntax_err_mess(char *token)
{
	ft_fprintf(2, "minishell : syntax error near unexpected token `%s'\n", token);
	return (1);
}

int syntax_error(t_node *head)
{
	// t_node *cpy;

	if (only_operator(head))
		return(syntax_err_mess(head->val));
	// cpy = node;
	// while (cpy)
	// {
	// 	cpy = cpy->next;
	// }
	
	return (0);
}
