/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:08:53 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:58:30 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/parsing.h"

int	only_operator(t_node *head)
{
	if (!head->next && head->token == OPERATOR)
		return (1);
	return (0);
}

int	syntax_err_mess(char *token_base, int selected)
{
	char *token;

	token = ft_strdup(token_base);
	if (selected == 0)
		ft_fprintf(2, "minishell : syntax error : unexpected token `%s'\n",
			token);
	if (selected == 2)
		ft_fprintf(2, "minishell : syntax error : unoppened token `%s'\n",
			&token[1]);
	token[1] = 0;
	if (selected == 1)
		ft_fprintf(2, "minishell : syntax error : unclosed token `%s'\n",
			token);
	free(token);
	return (1);
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

int	check_unclosed(char *c, t_node *node)
{
	t_node *cpy;
	int		count;

	cpy = node;
	count = 0;
	while (cpy)
	{
		if (!ft_strncmp(&c[0], cpy->val, 1))
			count++;
		if (!ft_strncmp(&c[1], cpy->val, 1))
			count--;
		cpy = cpy->next;
	}
	if (count > 0)
		return (1);
	if (count < 0)
		return (2);
	return (0);
}

int check_unclosed_quote(char *c, t_node *node)
{
    t_node *cpy;
    int     count;
    int     len;

    cpy = node;
    count = 0;
    while (cpy)
    {
        len = ft_strlen(cpy->val);
        if (len > 0 && cpy->val[0] == c[0])
        {
            if (len == 1 || cpy->val[len - 1] != c[0])
                count++;
        }
        cpy = cpy->next;
    }
    return (count % 2);
}

int	syntax_error(t_node *head)
{
	t_node	*cpy;

	if (only_operator(head))
		return (syntax_err_mess(head->val, 0));
	cpy = head;
	while (cpy)
	{
		if (unexpected_token(cpy))
			return (syntax_err_mess(cpy->val, 0));
		cpy = cpy->next;
	}
	if (check_unclosed("()", head) != 0)
		return (syntax_err_mess("()", check_unclosed("()", head)));
	if (check_unclosed_quote("\"", head) != 0)
		return (syntax_err_mess("\"\"", 1));
	if (check_unclosed_quote("'", head) != 0)
		return (syntax_err_mess("'", 1)); 
	return (0);
}
