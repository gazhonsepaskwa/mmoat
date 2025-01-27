/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:23:27 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 08:23:27 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "../../includes/env.h"

typedef enum e_state
{
	UNDEF,
	_AND,
	_OR,
	_CMD,
	_PLINE
}		t_state;

typedef enum e_redir
{
	_NR,
	_RED_L,
	_RED_R,
	_RED_DR
}		t_redir;

typedef struct s_ast_n
{
	t_state			state;
	struct s_ast_n	*parent;
	struct s_ast_n	*left;
	struct s_ast_n	*right;
	struct s_ast_n	**pline;
	int				ex_code;
	struct s_ast_n	*head;
	char			*cmd;
	char			**args;
	int				fds[2];
	int				_stdout;
	int				_stdin;
	t_redir			redir;
	char			*infile;
	char			*outfile;
	int				shlvl;
	char			**env;
}					t_ast_n;

t_ast_n	*return_hardcode_ast(char **envp);

#endif
