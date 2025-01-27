/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:35:29 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/27 12:35:29 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../lib/libft/libft.h"

static int	count_var(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		i++;
	return (i);
}

char	**init_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (count_var(envp) + 1));
	if (!env)
		return (NULL);
	env[count_var(envp)] = NULL;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}
