/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:04:44 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/14 10:04:44 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	syntax_err_mess(char *token_base, int selected)
{
	char	*token;

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
	if (selected == 3)
		ft_fprintf(2, "minishell : syntax error : unexpected end of file\n");
	free(token);
	return (1);
}

int	check_unclosed(char *c, t_node *node)
{
	t_node	*cpy;
	int		count;

	cpy = node;
	count = 0;
	while (cpy)
	{
		if (!ft_strncmp(&c[0], cpy->val, 1) && count >= 0)
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

bool	check_unclosed_quote(char *c, t_node *node)
{
	t_node	*cpy;
	int		i;
	bool	closed;
	bool	in_other_quote;

	closed = true;
	in_other_quote = false;
	cpy = node;
	while (cpy)
	{
		i = 0;
		while (cpy->val[i])
		{
			if ((cpy->val[i] == '"' || cpy->val[i] == '\'')
				&& cpy->val[i] != c[0] && closed)
				in_other_quote = !in_other_quote;
			if (cpy->val[i] == c[0] && !in_other_quote)
				closed = !closed;
			i++;
		}
		cpy = cpy->next;
	}
	if (!closed)
		return (true);
	return (false);
}
