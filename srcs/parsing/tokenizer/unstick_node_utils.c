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
	if (val[0] == '(' || val[0] == ')')
		i = 1;
	else
	{
		while (val[i] && ((is_meta(val[i]) && val[i] == ref)))
			i++;
	}
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

int	unic(int *meta)
{
	int	i;
	int	ref_meta;

	i = -1;
	ref_meta = meta[0];
	while (meta[++i] != -1)
		if (meta[i] != ref_meta)
			return (0);
	return (1);
}

void update_quote(char *quote, char cmp)
{
	if (*quote == 0 && (cmp == '"' || cmp == '\''))
		*quote = cmp;
	else if (*quote == cmp)
		*quote = 0;
	return ;
}

int	is_sticked(char *val)
{
	int		i;
	int		meta[1000];
	int		meta_it;
	int		unmeta;
	char	quote;

	i = -1;
	meta_it = 0;
	meta[0] = -1;
	unmeta = 0;
	quote = 0;
	while (val[++i])
	{
		update_quote(&quote, val[i]);
		if (is_meta(val[i]) && !quote)
			meta[meta_it++] = val[i];
		if (!is_meta(val[i]))
			unmeta = 1;
	}
	meta[meta_it] = -1;
	if ((meta[0] != -1 && unmeta) || !unic(meta) || (meta[0] == '('
			&& meta[1] == '(') || (meta[0] == ')' && meta[1] == ')'))
		return (1);
	return (0);
}
