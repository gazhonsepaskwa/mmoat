/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:54:00 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/29 08:54:00 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_tabstr(char **tab)
{
	int		i;
	int		alloc_count;
	char	*out;
	char	*tmp;

	i = -1;
	alloc_count = 0;
	while (tab[++i])
		alloc_count += ft_strlen(tab[i]) + 1;
	i = 0;
	out = tab[0];
	while (tab[++i])
	{
		tmp = out;
		out = ft_sprintf("%s %s", out, tab[i]);
		free(tmp);
	}
	out[alloc_count] = 0;
	return (out);
}
