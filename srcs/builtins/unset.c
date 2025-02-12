/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:36 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:19 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(char **arg, t_ast_n *head)
{
	int	i;
	int	ret;

	i = 0;
	if (count_args(arg) == 1)
		return (err_msg_cmd("unset", NULL, UNSET_ARG, EXIT_FAILURE));
	while (++i < count_args(arg))
		ret = remove_env_var(arg[i], head->msh);
	return (!ret);
}
