/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gnl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:23:57 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/04 22:13:16 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GNL_H
# define LIBFT_GNL_H
# include <stdlib.h> // malloc(), free()
# include <unistd.h> // read()
# ifndef BUFFER_SIZE
/*	Default BUFFER_SIZE for the read function, modifiable here or by adding
	-D BUFFER_SIZE=number to the compiling cc command.
*/
#  define BUFFER_SIZE 20000
# endif

char	*gnl_strbreak(const char *str);
size_t	gnl_strlen(const char *str);
char	*gnl_assemble(const char *state, const char *add);
char	*gnl_pack(char **state);
char	*gnl_recycle(char **state, char *linebreak);
ssize_t	gnl_read(int fd, char **state, char *buffer);
char	*gnl_cleanup(char **pointer);

char	*get_next_line(int fd);

#endif
