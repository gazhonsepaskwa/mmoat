/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:52:54 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/05 08:37:23 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include "../../libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_flags
{
	int	spec;
	int	width;
	int	precision;
	int	left;
	int	zero;
	int	hash;
	int	plus;
	int	space;
	int	fd;
}	t_flags;

// PRINTF

// PRINT ARGS
int		ft_print_char(unsigned char c, t_flags flags);
int		ft_print_c(unsigned char c, t_flags flags);
int		print_c(unsigned char c, int *check, t_flags flags);
int		ft_print_hex(unsigned int num, int uppercase, t_flags flags);
int		ft_print_int(int num, t_flags flags);
int		ft_print_us(unsigned int num, t_flags flags);
int		ft_print_s(char *str, t_flags flags);
int		ft_print_ptr(unsigned long add, t_flags flags);

// UTILS
int		hex_len(unsigned long num);
int		num_len(long n);
int		is_arg(char c);
int		get_size(int num, int len, t_flags flags);
int		get_ussize(unsigned int num, int len, t_flags flags);
int		get_hexsize(unsigned int nbr, int len, t_flags flags);
size_t	ft_strlen(const char *str);
char	*build_strn(char *str, long nbr, int len, t_flags flags);
char	*build_strusn(char *str, unsigned int nbr, int len);
char	*build_hexn(unsigned int nbr, char *hash, t_flags flags, char *base);
void	hex_hash(char *s, char *hash, int *i);
void	check_minus(char *str);

//FLAGS
t_flags	init_flags(t_flags flags, int fd);
t_flags	flag_left(t_flags flags);
int		flag_precision(const char *str, int i, t_flags *flags);
int		flag_width(const char *str, int i, t_flags *flags);
int		ft_print_width(t_flags flags, int size, int zero, int *check);

//FlAG UTILS
int		ft_isflag(char c);
int		is_flag(char c);
int		is_spec(char c);

#endif
