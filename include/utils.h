/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:10:37 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/06 15:16:24 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

// main

t_data		*data(void);
char		*get_shell_line(const char *prompt);
void		set_shell_level(void);

char		**gc_split(const char *s, char c);
void		gc_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		*gc_calloc(size_t count, size_t size);
char		*gc_substr(char const *string, unsigned int start, size_t length);
char		*gc_strdup(char const *string);
char		*gc_strjoin(char const *s1, char const *s2);
char		*gc_strjoin_3(char const *s1, char const *s2, char const *s3);
t_list		**gc_list(t_gc_index index);
void		gc_init(void);
t_list		*gc_add(void *memory);
void		gc_mode(t_gc_index mode);
void		gc_clear(t_gc_index index);
void		*gc_clear_one(void *content_ptr);
void		gc_clear_temporary(void);
void		gc_clear_all(void);
char		*gc_itoa(int number);
char		*gc_getcwd(void);
char		*gc_readline(char const *prompt);
char		*gc_get_next_line(int fd);
char		*save_getcwd(char *buf, size_t size);
DIR			*save_opendir(char *path);
void		save_dup2(int old_fd, int new_fd);
int			save_dup(int copy_fd);
void		save_pipe(int *write_in_pipe, int *read_out_pipe);
pid_t		save_fork(void);
void		save_close(int *fd);
void		close_files(t_file *head);
void		close_all_files(t_expression *root);
t_file		*file_make(void);
t_file		*file_dup_values(t_file *input);
void		file_append_front(t_file **start_ptr, t_file *add_file);
void		file_append_back(t_file **start_ptr, t_file *add_file);
t_file		*file_add_front(t_file **start_ptr);
t_file		*file_add_back(t_file **start_ptr);
t_file		*file_pop_front(t_file **start_ptr);
t_file		*file_pop_back(t_file **start_ptr);

#endif
