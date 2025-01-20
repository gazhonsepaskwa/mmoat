#include "tokenizer.h"

t_token	get_token(char *str)
{
	t_token	token;

	if (!strncmp(str, "&", 1) || !strncmp(str, "|", 1) || !strncmp(str, "(", 1)
		|| !strncmp(str, ")", 1) || !strncmp(str, "<", 1) || !strncmp(str, ">",
			1))
		token = OPERATOR;
	else
		token = WORD;
	return (token);
}

int	is_meta(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '"')
		return (1);
	return (0);
}

int	is_sticked(char *val)
{
	int	i;
	int	meta;
	int	unmeta;

	i = 0;
	meta = 0;
	unmeta = 0;
	while (val[i])
	{
		if (is_meta(val[i]))
			meta = 1;
		if (!is_meta(val[i]))
			unmeta = 1;
		i++;
	}
	if (meta && unmeta)
		return (1);
	return (0);
}
