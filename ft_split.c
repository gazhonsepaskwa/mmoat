/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:48:12 by lderidde          #+#    #+#             */
/*   Updated: 2024/07/25 14:13:12 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	check_sep(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	count_strings(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!(check_sep(str[i], charset))
			&& (check_sep(str[i + 1], charset)
				|| str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

void	build_str(char *charset, char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] && !(check_sep(src[i], charset)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	build_tab(char **tab, char *str, char *charset)
{
	int	i;
	int	count;
	int	j;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_sep(str[i], charset))
			i++;
		else
		{
			j = 0;
			while (!(check_sep(str[j + i], charset)) && str[j + i])
				j++;
			tab[count] = malloc(sizeof(char) * (j + 1));
			build_str(charset, &str[i], tab[count]);
			count++;
			i = i + j;
		}
	}
}

char	**ft_split(char *str, char *charset)
{
	int		count;
	char	**tab;

	count = count_strings(str, charset);
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	tab[count] = 0;
	build_tab(tab, str, charset);
	return (tab);
}
/*
#include <stdio.h>
int main (int argc, char **argv)
{
	int	i = 0;
	(void)argc;
	char **res = ft_split(argv[1], argv[2]);
	int len = count_strings(argv[1], argv[2]);
	while (i < len)
	{
		printf("%s\n", res[i]);
		free(res[i]);
		i++;
	}
	free(res);
}
*/
