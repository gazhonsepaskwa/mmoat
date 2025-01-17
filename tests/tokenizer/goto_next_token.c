#include "tokenizer.h"

int	goto_next_token(char *str)
{
	int			i;
	static char	last_token = '#';

	i = 0;
	if (is_meta_token(str[i]))
		i += skip_meta_token(&str[i]);
	else if (last_token != '<' && last_token != '>')
		i += go_to_next_meta_token(&str[i]);
	else
	{
		while (str[i] == ' ')
			i++;
		while (str[i] && str[i] != '&' && str[i] != '|'
			&& str[i] != '(' && str[i] != ')'
			&& str[i] != '<' && str[i] != '>'
			&& str[i] != ' ')
			i++;
	}
	last_token = str[0];
	return (i);
}
