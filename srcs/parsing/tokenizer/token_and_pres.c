/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_and_pres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:54:32 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:26:33 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_pres	get_operator(char *s)
{
	if (s[0] == '&' && s[1] && s[1] == '&')
		return (AND);
	else if (s[0] == '|' && s[1] && s[1] == '|')
		return (OR);
	else if (s[0] == '|' && !s[1])
		return (PIPE);
	else if (s[0] == '(' && !s[1])
		return (SUBSH_S);
	else if (s[0] == ')' && !s[1])
		return (SUBSH_E);
	else if (s[0] == '<' && s[1] && s[1] == '<')
		return (HEREDOC);
	else if (s[0] == '>' && s[1] && s[1] == '>')
		return (D_RED_R);
	else if (s[0] == '<' && !s[1])
		return (RED_L);
	else if (s[0] == '>' && !s[1])
		return (RED_R);
	return (UNDEFINED);
}

t_token	get_token(char *str)
{
	t_token	token;

	if (!ft_strncmp(str, "&", 1) || !ft_strncmp(str, "|", 1)
		|| !ft_strncmp(str, "(", 1) || !ft_strncmp(str, ")", 1)
		|| !ft_strncmp(str, "<", 1) || !ft_strncmp(str, ">", 1))
		token = OPERATOR;
	else
		token = WORD;
	return (token);
}

t_pres	get_pressision(char *s, t_token token, t_token last_token,
		t_pres last_pres)
{
	if (token == OPERATOR)
		return (get_operator(s));
	else if (last_token == OPERATOR && (last_pres == RED_R || last_pres == RED_L
			|| last_pres == D_RED_R))
		return (RED_FILE);
	else if (last_token == OPERATOR && last_pres == HEREDOC)
		return (LIM);
	else if (last_token == OPERATOR || last_token == UNSET)
		return (COMMAND);
	return (PARAMETER);
}
