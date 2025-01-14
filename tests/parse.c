#include "../includes/minishell.h"

void truncate_after_exit_word(char **lst)
{
	int	i;
	int	depth;
	int truncate_mode;

	i = 0;
	depth = 0;
	truncate_mode = FALSE;
	while (lst[i])
	{
		if (truncate_mode)
		{
			free(lst[i]);
			lst[i] = NULL;
		}
		else
		{
			if (lst[i][0] == '(')
				depth += 1;
			if (lst[i][ft_strlen(lst[i]) - 1] == ')')
				depth -= 1;
			if (!ft_strncmp(lst[i], "exit", 4) && depth == 0)
				truncate_mode = TRUE;
		}
		i++;
	}
}

/*void print_tab(char **lst)*/
/*{*/
/*	int i = 0;*/
/*	while (lst[i])*/
/*	{*/
/*		printf("%s\n", lst[i]);*/
/*		i++;*/
/*	}*/
/*}*/

int main (int ac, char **av)
{
	(void)ac;

	char *str = av[1];
	char **lst;

	if (str)
	{
		// replace by a custom split that also the token alone and under the form of a linked list
		lst = ft_split(str, ' ');
		truncate_after_exit_word(lst);
		print_tab(lst);
		free_tab(lst);
	}
}
