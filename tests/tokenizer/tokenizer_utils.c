#include "tokenizer.h"

t_token	get_token(char *str)
{
	t_token token;

	if (!strncmp(str, "&", 1) || !strncmp(str, "|", 1)
		|| !strncmp(str, "(", 1) || !strncmp(str, ")", 1)
		|| !strncmp(str, "<", 1) || !strncmp(str, ">", 1))
		token = OPERATOR;
	else
		token = WORD;
	return (token);
}
