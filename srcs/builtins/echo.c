#include "../../includes/builtins.h"

int	is_silentchar(char c)
{
	if (c == 'n' || c == '-' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_silent(char *str)
{
	int	i;

	i = 4;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] == '-')
	{
		i++;
		if (str[i] && str[i] == 'n')
			return (1);
	}
	return (0);
}

void	builtin_echo(char *arg)
{
	int	i;

	i = 4;
	while (arg[i] && is_silentchar(arg[i]))
		i++;
	printf("%s", &arg[i]);
	if (!is_silent(arg))
		printf("\n");
}
