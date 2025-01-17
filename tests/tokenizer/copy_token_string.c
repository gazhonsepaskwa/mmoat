/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_token_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:48:50  by nalebrun         #+#    #+#             */
/*   Updated: 2025/01/16 12:48:50  by nalebrun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h" 

int	is_meta_token(char c)
{
	if (c == '&' || c == '|'
		|| c == '(' || c == ')'
		|| c == '>' || c == '<')
		return (1);
	return (0);
}

int	skip_meta_token(char *str)
{
	int	i;

	i = 0;
	if ((str[i] == '&')
		|| (str[i] == '|' && str[i + 1] && str[i + 1] == '|')
		|| (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] && str[i + 1] == '>'))
		i = 2;
	else
		i = 1;
	return (i);
}

int	go_to_next_meta_token(char *str)
{
	int	i;

	i = 0;
	while (str [i]
		&& str[i] != '&'
		&& str[i] != '|'
		&& str[i] != '('
		&& str[i] != ')'
		&& str[i] != '<'
		&& str[i] != '>')
		i++;
	return (i);
}

static int	go_to_second_next_space_block(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*copy_token_string(char *str, char last_token)
{
	char	*out;
	char	*trimed_out;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (is_meta_token(str[i]))
		i += skip_meta_token(&str[i]);
	else if (last_token != '<' && last_token != '>')
		i += go_to_next_meta_token(&str[i]);
	else
		i += go_to_second_next_space_block(&str[i]);
	out = malloc(i + 1);
	if (!out)
		return (NULL);
	j = -1;
	while (++j < i)
		out[j] = str[j];
	out[j] = 0;
	trimed_out = ft_strtrim(out, " ");
	free(out);
	return (trimed_out);
}
