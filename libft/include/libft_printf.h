/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:41:46 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/23 18:32:46 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

/*	This macro determines how large the buffer within which number output
	strings are assembled will be. In this case, for possible future expansions:
	11111111 11111111 11111111 11111111 is 4,294,967,295 (UINT_MAX) in binary.
			8        16       24       32
	Binary is the worst case conversion, 64 is double that.
*/
# define PTF_NUM_BUFFER 64
# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef struct s_spec
{
	va_list	argument;
	int		fd;
	char	*string;
	int		specifier;
	int		left;
	int		width;
	int		precision;
	char	padding;
	char	sign;
	int		alt;
	int		length;
	int		read;
	int		written;
}			t_spec;

typedef int	(*t_conversion)(t_spec *);
typedef int	(*t_flag)(t_spec *);

/* --- helpers -------------------------------------------------------------- */

int			ptf_write_string(char *str, int max_length, t_spec *spec);
int			ptf_write_character(char c, t_spec *spec);
int			ptf_write_padding(int left, t_spec *spec);
int			ptf_write_precision(t_spec *spec);

int			ptf_padding(char c, int length, t_spec *spec);
char		ptf_convert(unsigned int value, unsigned int base);
char		*ptf_ntobase(unsigned int base, unsigned long long nbr,
				t_spec *spec);
char		*ptf_capitalize(char *number);
int			ptf_read_spec(const char *fmt, t_spec *spec);
int			ptf_reset_spec(t_spec *spec);
int			ptf_print_alt(t_spec *spec);
void		ptf_init_conversions(t_conversion *conversions);
void		ptf_init_flags(t_flag *flags);

/* --- handlers ------------------------------------------------------------- */

int			ptf_c(t_spec *spec);
int			ptf_s(t_spec *spec);
int			ptf_id(t_spec *spec);
int			ptf_u(t_spec *spec);
int			ptf_x(t_spec *spec);
int			ptf_p(t_spec *spec);
int			ptf_o(t_spec *spec);
int			ptf_percent(t_spec *spec);
int			ptf_r(t_spec *spec);
int			ptf_b(t_spec *spec);

int			ptf_flag_left(t_spec *spec);
int			ptf_flag_zero(t_spec *spec);
int			ptf_flag_precision(t_spec *spec);

int			ptf_flag_space(t_spec *spec);
int			ptf_flag_alt(t_spec *spec);
int			ptf_flag_plus(t_spec *spec);

/* --- main function -------------------------------------------------------- */

int			ft_vfprintf(int fd, const char *format, va_list arguments);
int			ft_fprintf(int fd, const char *format, ...);
int			ft_debugf(const int level, const char *format, ...);
int			ft_printf(const char *format, ...);

#endif
