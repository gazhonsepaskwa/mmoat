#include "tokenizer.h"

char	*copy_meta_xor(char *val, int *copied, int rev)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (is_meta(val[i]) ^ rev)
	{
		if (!rev && val[i] != val[0])
			break ;
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
