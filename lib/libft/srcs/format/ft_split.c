/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:15:47 by nalebrun          #+#    #+#             */
/*   Updated: 2024/11/27 12:58:41 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	**free_all(char **tab, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	count_strings(char const *s, char *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (!is_charset(*s, set) && is_charset(*(s + 1), set)
				|| *(s + 1) == '\0')
			count ++;
		s++;
	}
	return (count);
}

static	void	build_str(char const *src, char *dest, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !is_charset(src[i], set))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static	char	**build_tab(char **tab, char const *s, char *set)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (tab && s[i])
	{
		if (is_charset(s[i], set))
			i++;
		else
		{
			j = 0;
			while (!is_charset(s[i + j], set) && s[i + j])
				j++;
			tab[count] = ft_calloc((j + 1), sizeof(char));
			if (!tab[count])
				return (free_all(tab, count));
			build_str(&s[i], tab[count++], set);
			i = i + j;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char *set)
{
	int		count;
	char	**tab;

	count = count_strings(s, set);
	tab = ft_calloc(count + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab[count] = 0;
	tab = build_tab(tab, s, set);
	return (tab);
}
