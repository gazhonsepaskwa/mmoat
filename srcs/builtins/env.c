/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:04 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:32 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(char **arg, char **envp)
{
	int	i;

	i = 0;
	if (count_args(arg) > 1)
	{
		err_msg_cmd("env", NULL, "too many arguments", 1);
		return (1);
	}
	while (envp[i])
	{
		if (envp[i][0] && ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
