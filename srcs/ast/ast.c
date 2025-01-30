/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/30 13:19:40 by lderidde         ###   ########.fr       */
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
	if (prt)
		node->shlvl = prt->shlvl;
	else
		node->shlvl = 0;
	node->env = NULL;
	return (node);
}

static int	count_var(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		i++;
	return (i);
}

static char	**init_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (count_var(envp) + 1));
	if (!env)
		return (NULL);
	env[count_var(envp)] = NULL;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

void	setup_cmd(t_ast_n *node, char *cmd, char *args)
{
	node->cmd = ft_strdup(cmd);
	node->args = ft_split(args, " ");
}

t_ast_n	*return_hardcode_ast(char **envp)
{
	t_ast_n 		*head;

	// head = created_ast_n(_CMD, NULL, NULL);
	// head->head = head;
	// setup_cmd(head, "sdd", "ls -l");	
	head = created_ast_n(_AND, NULL, NULL);
	head->env = init_env(envp);
	head->left = created_ast_n(_CMD, head, head);
	setup_cmd(head->left, "export", "export test=");
	// head->right = created_ast_n(_AND, head, head);
	// head->right->left = created_ast_n(_CMD, head->right, head);
	// setup_cmd(head->right->left, "echo", "echo $PWD");
	// head->right->right = created_ast_n(_CMD, head->right, head);
	// setup_cmd(head->right->right, "ls", "ls -l");
	head->right = created_ast_n(_PLINE, head, head);
	head->right->pline = malloc(sizeof(t_ast_n *) * 5);
	head->right->pline[0] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[0], "export", "export");
	head->right->pline[1] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[1], "grep", "grep test");
	head->right->pline[2] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[2], "cat", "cat");
	head->right->pline[3] = created_ast_n(_CMD, head->right, head);
	setup_cmd(head->right->pline[3], "cat", "cat");
	head->right->pline[1]->redir = _RED_R;
	head->right->pline[1]->outfile = "file";
	// head->right->pline[3]->redir = _RED_R;
	// head->right->pline[3]->outfile = "file";
	head->right->pline[4] = NULL;
	return (head);
}
