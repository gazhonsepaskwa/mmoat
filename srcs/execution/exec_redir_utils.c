/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:13:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/13 15:13:52 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_redir(t_ast_n *node, int i)
{
	if (node->redir[i] == _RED_L)
	{
		dup2(node->_stdin, STDIN_FILENO);
		close(node->_stdin);
	}
	else if (node->redir[i] == _RED_R || node->redir[i] == _RED_DR)
	{
		dup2(node->_stdout, STDOUT_FILENO);
		close(node->_stdout);
	}
}
