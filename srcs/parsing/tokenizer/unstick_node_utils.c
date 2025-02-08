/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstick_node_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:53:08 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/03 12:53:08 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*copy_meta(char *val, int *copied)
{
	int		i;
	int		j;
	char	*out;
	char	ref;

	i = 0;
	ref = val[0];
	while (val[i] && ((is_meta(val[i]) && val[i] == ref)))
		i++;
	*copied = i;
	out = malloc(i + 1);
	j = -1;
	while (++j < i)
		out[j] = val[j];
	out[i] = 0;
	return (out);
}

char	*copy_unmeta(char *val, int *copied)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (val[i] && !is_meta(val[i]))
		i++;
	*copied = i;
	out = malloc(i + 1);
	j = -1;
	while (++j < i)
		out[j] = val[j];
	out[i] = 0;
	return (out);
}
