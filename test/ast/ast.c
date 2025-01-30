/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 08:22:16 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	setup_cmd(t_ast_n *node, char *cmd, char *args)
{
	node->cmd = ft_strdup(cmd);
	node->args = ft_split(args, " ");
}

int	last_tok_subsh(t_node *lst)
{
	while (lst)
	{
		if (lst->next == NULL && !ft_strncmp(lst->val, ")", 1))
			return (1);
		lst = lst->next;
	}
	return (0);
}

skip_parentheses(t_node **lst)
{
	if (!ft_strncmp((*lst)->val, "(", 1))
	{
		while ((*lst)->next && ft_strncmp((*lst)->next->val, ")", 1))
		{
			if (!ft_strncmp((*lst)->val, "(", 1))
				skip_parentheses(&lst);
			*lst = (*lst)->next;
		}
	}
}

t_node	*find_token(char *tok, t_node *lst)
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

/*t_ast_n	create_ast_n(t_node *lst, t_ast_n *parent);*/

/*void	create_and_or(t_ast_n *parrent, t_node *lst, t_node *token)*/
/*{*/
/*	t_node **sublsts;*/
/**/
	/*sublsts = cutll(lst, token);*/
/*	parrent->left = create_ast_n(sublsts[0], parrent);*/
/*	parrent->left = create_ast_n(sublsts[1], parrent);*/
/*	free_lltab(sublsts);*/
/*	free(token);*/
/*}*/


/*void	create_cmd(t_ast_n *parent, t_node *lst, t_node *token)*/
/*{*/
/*}*/

/*void	create_pline(t_ast_n *parent, t_node *lst, t_node *token)*/
/*{*/
/*}*/

t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent)
{
	t_ast_n *node;
	t_node	*token;

	node = malloc(sizeof(t_ast_n));
	token = get_top_token(lst, &node->state);

	(void)token;
	(void)parent;

	node->left = NULL;
	node->right = NULL;
	node->pline = NULL;

	/*if (node->state == _PLINE)*/
		/*create_pline(node, lst, token);*/
	/*else if (node->state == _CMD)*/
		/*create_cmd(node, lst, token);*/
	/*else if (node->state == _SUBSH)*/
		/*create_subsh(node, lst, token);*/
	/*else*/
		/*create_and_or(node, lst, token);*/

	return (node);
}

t_ast_n	*get_ast(char **envp, t_node *lst)
{
	t_ast_n *head;
	(void)envp;

	head = create_ast_n(lst, NULL);
	return (head);
}
