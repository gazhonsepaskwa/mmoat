/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_keep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:31:48 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/21 11:31:48 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	count_strings(char const *s, char *set)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!is_charset(*s, set) && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (is_charset(*s, set))
			in_word = 0;
		s++;
	}
	return (count);
}

static void	build_str(char const *src, char *dest, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !is_charset(src[i], set))
	{
		dest[i] = src[i];
		i++;
	}
	while (src[i] && is_charset(src[i], set))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**alloc_tab(char const *s, char *set)
{
	int		count;
	char	**tab;

	count = count_strings(s, set);
	tab = ft_calloc(count + 1, sizeof(char *));
	return (tab);
}

static char	**build_tab(char **tab, char const *s, char *set)
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
			while (s[i + j] && !is_charset(s[i + j], set))
				j++;
			while (s[i + j] && is_charset(s[i + j], set))
				j++;
			tab[count] = ft_calloc((j + 1), sizeof(char));
			if (!tab[count])
				return (free_all(tab, count));
			build_str(&s[i], tab[count++], set);
			i += j;
		}
	}
	return (tab);
}

char	**ft_split_keep(char const *s, char *set)
{
	char	**tab;

	tab = alloc_tab(s, set);
	if (!tab)
		return (NULL);
	tab = build_tab(tab, s, set);
	return (tab);
}
