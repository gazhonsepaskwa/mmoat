/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:25:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/18 13:06:08 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "../lib/libft/libft.h"
# include "parser/ast.h"
# include "parser/drawio.h"
# include "parser/tokenizer.h"
# include "parser/parsing.h"
# include "parser/heredoc.h"
# include "exec/builtins.h"
# include "exec/env.h"
# include "exec/exec.h"
# include "exec/expander.h"

# define DEBUG 1

# ifndef DIO_PATH
#  define DIO_PATH "ast.xml"
# endif

typedef struct s_ast_n	t_ast_n;
typedef struct s_node	t_node;
typedef struct s_msh	t_msh;

typedef struct s_msh
{
	int		ex_code;
	t_ast_n	*head;
	int		here_fd;
	char	*input;
	char	*prev_input;
	int		hist;
	char	**env;
}			t_msh;

t_msh	*init_msh(char **envp);
void	free_msh(t_msh *msh);
void	free_child(t_msh *msh);
void	init_sig(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
char	*powerline(t_msh *msh);

# define POW1 "\001\033[1;38;2;21;22;26;48;2;92;106;178m\002"
# define POW2 "\001\033[1;38;2;92;106;178;48;2;54;54;54m\002"
# define POW3 "\001\033[1;38;2;54;54;54;48;2;39;39;39m\002"
# define POW4 "\001\033[0;38;2;204;205;209;48;2;39;39;39m\002"
# define POW5 "\001\033[1;38;2;39;39;39m\002"
# define SEP "\001\033[38;2;64;64;64m\002"

#endif
