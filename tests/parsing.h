/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:45:28 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 14:45:28 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "tokenizer/tokenizer.h"
# include "ast/ast.h"
# include "drawio/drawio.h"

// drawio

// tmp_env
char	**init_env(char **envp);

#endif
