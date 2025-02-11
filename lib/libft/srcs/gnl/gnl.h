/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:46:20 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 11:56:11 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "../../libft.h"

char			*ft_strjoin_gnl(char *s1, char *s2);
void			*f_calloc(int size, int nb);
int				ft_strchr_index(char *s, int c);
char			*get_next_line(int fd, int del);
// size_t	ft_gstrlen(const char *str, int j);
// char	*ft_strichr(const char *s, int c, int i);

#endif
