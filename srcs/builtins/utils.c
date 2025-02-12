/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:41 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:16 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	char_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}
