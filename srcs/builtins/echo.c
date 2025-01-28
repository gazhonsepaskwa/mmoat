/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:31:56 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 12:40:27 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_silent(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (str[i] && str[i] != '-')
		return (flag);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		flag = true;
	return (flag);
}

char	*ft_getenv(char *str, char **envp)
{
	char	*tmp;
	int		j;
	size_t	len;

	j = 0;
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (envp[j] && ft_strnstr(envp[j], tmp, len) == NULL)
		j++;
	if (!envp[j])
		return (free(tmp), NULL);
	free(tmp);
	return (&envp[j][len]);
}

int	extractenv(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	if (i >= 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	free(tmp);
	if (var)
		ft_printf("%s", var);
	return (i);
}

static void	echo_print(char **arg, int j, char **envp)
{
	int	i;

	while (arg[j])
	{
		i = 0;
		while (arg[j][i])
		{
			if (arg[j][i] == '$')
			{
				if (!arg[j][i + 1] || arg[j][i + 1] == ' ')
					ft_put_c(arg[j][i++]);
				else
					i += extractenv(&arg[j][i], envp);
			}
			else
				ft_put_c(arg[j][i++]);
		}
		j++;
		if (arg[j])
			ft_put_c(' ');
	}
}

int	builtin_echo(char **arg, char **envp)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	while (arg[i] && is_silent(arg[i]))
	{
		flag = true;
		i++;
	}
	echo_print(arg, i, envp);
	if (!flag)
		ft_printf("\n");
	return (0);
}
