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

t_ast_n	*created_ast_n(t_state st, t_ast_n *prt, t_ast_n *he)
{
	t_ast_n *node;

	node = malloc(sizeof(t_ast_n));
	if (!node)
		return (NULL);
	node->state = st;
	node->parent = prt;
	node->head = he;
	node->ex_code = 0;
	node->cmd = NULL;
	node->args = NULL;
	node->_stdout = 1;
	node->_stdin = 0;
	node->redir = _NR;
	node->infile = NULL;
	node->outfile = NULL;
	node->left = NULL;
	node->right = NULL;
	node->pline = NULL;
	if (prt)
		node->shlvl = prt->shlvl;
	else
		node->shlvl = 0;
	node->env = NULL;
	return (node);
}

void	setup_cmd(t_ast_n *node, char *cmd, char *args)
{
	node->cmd = ft_strdup(cmd);
	node->args = ft_split(args, " ");
}

t_ast_n	*return_hardcode_ast(char **envp)
{
	t_ast_n 		*head;

	head = created_ast_n(_AND, NULL, NULL);
	head->env = init_env(envp);
	head->left = created_ast_n(_CMD, head, head);
	setup_cmd(head->left, "echo", "echo coucou");
	head->right = created_ast_n(_PLINE, head, head);
	head->right->pline = malloc(sizeof(t_ast_n *) * 4);
	head->right->pline[0] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[0], "ls", "ls");
	head->right->pline[1] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[1], "cat", "cat -e");
	head->right->pline[2] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[2], "wc", "wc -l");
	head->right->pline[3] = NULL;
	return (head);
}
