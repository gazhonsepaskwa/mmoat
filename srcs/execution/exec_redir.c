/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:42:31 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/13 15:16:21 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_file(t_ast_n *node, int check, int i)
{
	int	fd;

	if (check == 1 && access(node->files[i], F_OK))
	{
		ft_fprintf(2, "%s: %s\n", node->files[i], "No such file or directory");
		return (1);
	}
	if (check == 1)
		fd = open(node->files[i], O_RDONLY);
	else if (check == 2)
		fd = open(node->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (check == 3)
		fd = open(node->files[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_fprintf(2, "%s: %s\n",node->files[i], "Permission denied");
		return (1);
	}
	if (check == 1)
		node->_stdin = fd;
	else if (check == 2 || check == 3)
		node->_stdout = fd;
	return (0);
}

static void	save_stds(t_ast_n *node)
{
	if (node->state == _PLINE || node->redir[0] != _NR)
	{
		node->save_stdo = dup(STDOUT_FILENO);
		node->save_stdi = dup(STDIN_FILENO);
	}
}

int	handle_redir(t_ast_n *node)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	save_stds(node);
	while (node->state != _PLINE && node->redir[++i] && node->redir[i] != _NR)
	{
		if (node->redir[i] == _RED_L)
			check = handle_file(node, 1, i);
		else if (node->redir[i] == _RED_R)
			check = handle_file(node, 2, i);
		else if (node->redir[i] == _RED_DR)
			check = handle_file(node, 3, i);
		else if (node->redir[i] == _RED_DL)
			here_doc(node, i);
		if (check == 1)
			return (1);
		dup_redir(node, i);
	}
	return (0);
}

void	reset_redir(t_ast_n *node)
{
	if (node->state == _PLINE || node->redir[0] != _NR)
	{
		dup2(node->save_stdo, STDOUT_FILENO);
		close(node->save_stdo);
		dup2(node->save_stdi, STDIN_FILENO);
		close(node->save_stdi);
	}
}

int	err_fork_pline(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
	perror("fork");
	return (1);
}
