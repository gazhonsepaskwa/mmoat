/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:23:41 by  nalebrun         #+#    #+#             */
/*   Updated: 2025/01/20 13:15:47 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer/tokenizer.h"
/*#include "../includes/env.h"*/

void	truncate_comment(char *str)
{
	int		i;
	char	inquote;

	if (!str)
		return ;
	i = 0;
	inquote = 0;
	while (str[i])
	{
		if (!inquote && (str[i] == 39 || str[i] == '"'))
			inquote = str[i];
		else if (inquote && (str[i] == inquote))
			inquote = 0;
		if (str[i] == '#' && !inquote && str[i - 1] && str[i - 1] != '\\')
		{
			str[i] = 0;
			return ;
		}
		i++;
	}
}

void gen_dio_linked_list(t_node *head, char *fp)
{
	int fd;
	t_dio_elem rect;
	t_dio_elem arrow;
	t_node *current;

	current = head;
	fd = drawio_init(fp);
	rect.type = RECT;
	rect.rounded = 0;
	rect.x = 50;
	rect.y = 50;
	rect.w = 100;
	rect.h = 50;
	arrow.id_src = 0;
	arrow.type = ARROW;
	while (current != NULL)
	{
		rect.text = ft_sprintf("%s", current->val);
		arrow.id_dst = drawio_create_elem(fd, &rect);
		drawio_create_elem(fd, &arrow);
		arrow.id_src = arrow.id_dst;
		rect.x += 150;
		free(rect.text);
		current = current->next;
	}
	drawio_end_file(fd);
}

/*static t_data	*init_data(char **envp)*/
/*{*/
/*	t_data	*data;*/
/**/
/*	data = malloc (sizeof(t_data));*/
/*	data->env = init_env(envp);*/
/*	return (data);*/
/*}*/

int	main(int ac, char **av, char **envp)
{
	t_node	*lst;

	(void)ac;
	(void)envp;

	if (ac != 3)
	{
		ft_error("./test drawio_file command_str\n");
		return (1);
	}

	/*t_data data;*/

	/*data = init_data(envp);*/
	truncate_comment(av[1]);
	lst = tokenize(av[2]);
	if (!lst)
		return (1);
	debug_linked_list(lst, "Tokenized");
	gen_dio_linked_list(lst, av[1]);
	free_linked_list(lst);
}
