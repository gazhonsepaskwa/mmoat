/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:42:53 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:45:31 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interpret_cmd(char **input, t_msh *msh)
{
	msh->head = parser(*input, msh);
	if (!msh->head)
	{
		ft_free(input);
		return ;
	}
	msh->here_fd = open(".heredoc", O_RDONLY);
	msh->ex_code = execute_command(msh->head);
	get_next_line(msh->here_fd, 1);
	if (msh->here_fd != -1)
		close(msh->here_fd);
	unlink(".heredoc");
	free_ast(msh->head);
	msh->head = NULL;
	ft_free(input);
}
