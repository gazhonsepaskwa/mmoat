/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:20 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:24 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_export_valid(char *str)
{
	char	*equal;
	char	*key_end;

	if (!ft_isalpha(*str) && str[0] != '_')
		return (0);
	equal = ft_strchr(str, '=');
	if (equal)
	{
		if (equal != str && *(equal - 1) == '+')
			key_end = equal - 1;
		else
			key_end = equal;
	}
	else
		key_end = str + ft_strlen(str);
	while ((++str) < key_end)
	{
		if (!ft_isalnum(*str) && *str != '_')
		   return (0);
	}
	return (1);
}

char	**key_value(char *str)
{
	char	**tmp;
	char	*save;
	char	*equal;
	char	*key_end;

	tmp = malloc(sizeof(char *) * (2 + 1));
	if (!tmp)
		return (NULL);
	equal = ft_strchr(str, '=');
	if (*(equal - 1) == '+')
		key_end = equal - 1;
	else
		key_end = equal;
	tmp[0] = ft_substr(str, 0, key_end - str);
	if (equal - str == 0)
		tmp[1] = ft_strdup("");
	else
	{
		save = ft_substr(equal, 1, ft_strlen(equal) - 1);
		tmp[1] = ft_strtrim(save, "\"");
		free(save);
	}
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
		free_tab(print);
	}
}

int	print_export(char **envp)
{
	int		i;
	int		j;
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
			if (ft_strncmp(envp[j], envp[j + 1],
					ft_strchr(envp[j], '=') - envp[j]) > 0)
				char_swap(&envp[j], &(envp[j + 1]));
			j++;
		}
	}
	print_arr(envp);
	return (0);
}

int	builtin_export(char **arg, t_ast_n *head)
{
	int		i;

	i = 0;
	if (count_args(arg) == 1)
		return (print_export(head->msh->env));
	while (++i < count_args(arg))
	{
		if (is_export_valid(arg[i]))
			set_new_export(arg[i], head);
		else
			return (err_msg_cmd("export", arg[i], EXPRT_INV, 1));
	}
	return (0);
}
