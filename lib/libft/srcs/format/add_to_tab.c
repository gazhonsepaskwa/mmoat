/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:59:01 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/04 09:59:01 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h" 

static void	free_null_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

static char	**add_space_to_tab(char **tab, int count)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	new_env[count] = NULL;
	while (tab[i] && i < count)
	{
		new_env[i] = ft_strdup(tab[i]);
		free_null_ptr(tab[i]);
		i++;
	}
	free_null_ptr(tab);
	return (new_env);
}

void	add_to_tab(char ***tab, char *str)
{
	char	**tmp;
	int		i;

	if (!str)
		return ;
	tmp = *tab;
	i = 0;
	if (*tab)
	{
		while ((*tab) && (*tab)[i])
			i++;
		*tab = add_space_to_tab(*tab, i + 1);
	}
	else
	{
		*tab = malloc(sizeof(char *) * 2);
	}
	free(tmp);
	(*tab)[i] = ft_strdup(str);
	(*tab)[i + 1] = NULL;
}
