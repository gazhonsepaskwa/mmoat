/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:25:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:22:16 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 1

typedef struct s_ast_n t_ast_n;
typedef struct s_node t_node;

typedef struct s_msh
{
	int		ex_code;
	t_ast_n	*head;
	char	*input;
	int		hist;
	char	**env;
}			t_msh;

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# include "../lib/libft/libft.h"
# include "parser/ast.h"
# include "parser/drawio.h"
# include "parser/tokenizer.h"
# include "parser/parsing.h"
# include "exec/builtins.h"
# include "exec/env.h"
# include "exec/exec.h"
# include "exec/expander.h"

t_msh *init_msh(char **envp);
void  	free_msh(t_msh *msh);
void	free_child(t_msh *msh);

# define POW1 "\033[1;38;2;21;22;26;48;2;92;106;178m"
# define POW2 "\033[1;38;2;92;106;178;48;2;54;54;54m"
# define POW3 "\033[1;38;2;54;54;54;48;2;39;39;39m"
# define POW4 "\033[0;38;2;204;205;209;48;2;39;39;39m"
# define POW5 "\033[1;38;2;39;39;39m"

#endif
