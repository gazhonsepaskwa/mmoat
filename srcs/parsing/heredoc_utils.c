/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:41:03 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:41:03 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_heredoc(char *limiter, t_msh *msh, t_node *lst)
{
	ft_fprintf(2, "\n");
	ft_fprintf(1, "%s\n", limiter);
	free_linked_list(lst);
	free_msh(msh);
	exit(EXIT_SUCCESS);
}

void	end_heredoc(char *buf, t_msh *msh, t_node *lst)
{
	ft_fprintf(1, "%s\n", buf);
	free_msh(msh);
	free_linked_list(lst);
	exit(EXIT_SUCCESS);
}
