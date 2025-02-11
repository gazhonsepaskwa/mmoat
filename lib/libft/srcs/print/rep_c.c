/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:19:40 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/10 10:19:40 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*rep_c(char c, int count)
{
	char	*out;

	out = malloc(sizeof(char) * (count + 1));
	ft_memset(out, c, count);
	out[count] = 0;
	return (out);
}
