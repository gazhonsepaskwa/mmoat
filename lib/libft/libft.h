/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:33:28 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 11:57:07 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 1

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>

# include "colors.h"
# include "general.h"
# include "srcs/drawio/lib_drawio.h"

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		is_only_space(char *str);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

int		ft_toupper(int c);
int		ft_tolower(int c);

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);

void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

char	**ft_split(const char *s, char *set);
char	**ft_split_keep(const char *s, char *set);
char	*ft_tabstr(char **tab);
int		is_charset(char c, char *set);
void	free_tab(char **tab);
char	**free_all(char **tab, int count);
void	add_to_tab(char ***tab, char *str);

void	ft_put_c_fd(char c, int fd);
void	ft_put_s_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_put_i_fd(int n, int fd);
int		ft_put_ui_base(unsigned int nbr, char *base);
int		ft_put_uli_base(unsigned long int nbr, char *base);
int		ft_put_c(char c);
int		ft_put_s(char *s);
int		ft_put_i(int n);
int		ft_put_ui(unsigned int n);
void	ft_error(char *e);

int		ft_printf(const char *fstr, ...);
int		ft_fprintf(int fd, const char *str, ...);
char	*ft_sprintf(const char *str, ...);
char	*ft_strfjoin(char *s1, char *s2);
int		ft_debug(const char *fstr, ...);
char	*rep_c(char c, int count);

char	*get_next_line(int fd, int del);

void	ft_free(char **p);
void	ft_free_v(void **p);

#endif
