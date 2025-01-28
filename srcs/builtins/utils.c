/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 10:53:44 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	err_msg_cmd(char *cmd, char *arg, char *msg, int code)
{
	if (arg != NULL)
		ft_fprintf(2, "minishell: %s: %s: %s\n", cmd, arg, msg);
	else
		ft_fprintf(2, "minishell: %s: %s\n", cmd, msg);
	return (code);
}

int	count_args(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}
