/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:30 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/24 14:32:30 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	count_char(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			count++;
		i++;
	}
	return (count);
}

void	builtin_pwd(char *arg)
{
	char	*cwd;

	if (count_char(arg) > 3)
		ft_putendl_fd("pwd: too many arguments", 2);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
		{
			printf("%s\n", cwd);
			free(cwd);
		}
		if (!cwd)
			perror("pwd");
	}
}
