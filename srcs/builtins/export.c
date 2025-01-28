/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:20 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 10:19:06 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	free_tmp(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**key_value(char *str)
{
	char	**tmp;
	char 	*equal;

	tmp = malloc(sizeof(char *) * (2 + 1));
	if (!tmp)
		return (NULL);
	equal = ft_strchr(str, '=');
	tmp[0] = ft_substr(str, 0, equal - str);
	if (equal - str == 0)
		tmp[2] = ft_strdup("");
	else
		tmp[1] = ft_substr(equal, 1, ft_strlen(equal));
	tmp[2] = NULL;
	return (tmp);
}

void	print_arr(char **envp)
{
	int		i;
	char	*equal;
	char	**print;

	(void)equal;
	i = -1;
	while (envp[++i])
	{
		print = key_value(envp[i]);
		if (print[1])
			ft_printf("declare -x %s=\"%s\"\n", print[0], print[1]);
		else
			ft_printf("declare -x %s\n", print[0]);
		free_tmp(print);
	}
}

int	print_export(char **envp)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	i = -1;
	len = 0;
	while (envp[len])
		len++;
	while (++i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strchr(envp[j], '=') - envp[j]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
	}
	print_arr(envp);
	return (0);
}

int	builtin_export(char **arg, t_ast_n *head)
{
	int	i;
	char	**tmp;

	i = 0;
	if (count_args(arg) == 1)
		return (print_export(head->env));
	while (++i < count_args(arg))
	{
		if (ft_strchr(arg[i], '=') != NULL)
		{
			tmp = key_value(arg[i]);
			if (!tmp)
				return (1);
			set_var_env(tmp[0], tmp[1], head);
			free_tmp(tmp);
		}
		else
			set_var_env(arg[i], NULL, head);
	}
	return (0);
}
