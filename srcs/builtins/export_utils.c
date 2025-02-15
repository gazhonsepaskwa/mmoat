/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:22:24 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/15 13:22:24 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_append(char *str)
{
	if (*(ft_strchr(str, '=') - 1) == '+')
		return (1);
	else
		return (0);
}

void	set_new_export(char *str, t_ast_n *node)
{
	char	**tmp;

	if (ft_strchr(str, '=') != NULL)
	{
		tmp = key_value(str);
		if (!tmp)
			return ;
		if (is_append(str))
			append_var(tmp[0], tmp[1], node->msh);
		else
			set_var_env(tmp[0], tmp[1], node->msh);
		free_tab(tmp);
	}
	else
		set_var_env(str, NULL, node->msh);
}
