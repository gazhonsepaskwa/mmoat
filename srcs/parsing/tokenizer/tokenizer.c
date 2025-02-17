/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:57 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:30 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
//
// char *get_til_nxt_quote(char **str, char quote)
// {
// 	char	*base;
// 	char	*tmp;
// 	char	*out;
// 	int		len;
//
// 	base = *str;
// 	len = 1;
// 	tmp = NULL;
// 	if (**str)
// 		(*str)++;
// 	while ((**str) && **str != quote)
// 	{
// 		len++;
// 		(*str)++;
// 	}
// 	out = ft_substr(base, 0, len + 1);
// 	if (**str)
// 		(*str)++;
// 	if (**str && *(*str) && (*(*str) == '"' || *(*str) == '\'')) 
// 	{
// 		tmp = get_til_nxt_quote(str, **str);
// 	}
// 	out = ft_strfjoin(out, tmp);
// 	ft_free(&tmp);
// 	return (out);
// }
//

bool is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	else
	 return (false);
}

int	skip_quote(char *str)
{
	int i;

	if (!str[1])
		return 0;
	i = 1;
	while(str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}

int	goto_nxt_space(char *str)
{
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] && !is_space(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quote(&(str[i]));
		i++;
	}
	return (i);
}

static t_node	*tokenize_base(char *str)
{
	t_node	*lst;
	char	*tmp;
	int		i;
	int		len;

	lst = NULL;
	tmp = NULL;
	i = 0;
	while (str[i])
	{
		len = goto_nxt_space(&(str[i]));
		tmp = ft_substr(&str[i], 0, len);
		add_node_back(&lst, tmp, 0, 0);
		ft_free(&tmp);
		i += len;
	}
	return (lst);
}

static void	del_void_nodes(t_node **head)
{
	t_node	*cpy;
	t_node	*tmp;

	cpy = *head;
	if (ft_strlen((*head)->val) == 0)
	{
		cpy = (*head)->next;
		free((*head)->val);
		free(*head);
	}
	*head = cpy;
	while (cpy)
	{
		if (cpy->next && ft_strlen(cpy->next->val) == 0)
		{
			tmp = cpy->next->next;
			free(cpy->next->val);
			free(cpy->next);
			cpy->next = tmp;
		}
		cpy = cpy->next;
	}
}

t_node	*tokenize(char *str)
{
	t_node	*head;

	head = tokenize_base(str);
	if (!head)
		return (NULL);
	debug_token_list(head, "base");
	if (!trim_nodes(head))
		return (NULL);
	debug_token_list(head, "trim");
	del_void_nodes(&head);
	debug_token_list(head, "del void");
	set_token(head);
	debug_token_list(head, "set token");
	// if (syntax_error(head))
		// return (free_linked_list(head), NULL);
	return (head);
}
