/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:59:40 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/22 19:40:16 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdlib.h>	// malloc, free, getenv, exit
# include <unistd.h>	// read, write, close, access, fork, execve, pipe, dup, dup2, chdir, getcwd, isatty, unlink, ttyslot, ttyname
# include <fcntl.h>		// open, (O_* flags)
# include <dirent.h>	// opendir, readdir, closedir

// # include <sys/types.h>	// pid_t and other system types
# include <sys/wait.h>	// wait, waitpid, wait3, wait4
// # include <sys/time.h>	// timeval (used by wait3/wait4)
// # include <sys/resource.h> // rusage (used by wait3/wait4)
# include <errno.h>		// (errno)
# include <string.h>	// strerror
// # include <sys/stat.h>	// stat, lstat, fstat

// # include <termios.h>	// tcsetattr, tcgetattr
// # include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill
// # include <sys/ioctl.h>	// ioctl
# include <stdio.h>		// printf, perror
# include <stdbool.h>	// bool type (is not a function)
# include <limits.h>	// INT_MAX, PATH_MAX (is not a function)

# include "libft.h"
# include "libft_printf.h"
# include "libft_styles.h"
# include "execution.h"
# include "parsing.h"
# include "public_struct.h"


// auto
void		blt_cd(t_expression *cmd);
void		blt_cd_error_check(t_expression *cmd);
char		*blt_cd_get_new_dir(t_expression *cmd);
void		blt_echo(t_expression *cmd);
bool		h_is_n_flag(char *str);
void		blt_env(t_expression *cmd);
void		blt_exit(t_expression *cmd);
void		blt_export(t_expression *cmd);
void		blt_pwd(t_expression *cmd);
void		blt_unset(t_expression *cmd);
void		try_builtin(t_expression *command);
int			blt_count_args(t_expression *cmd);
bool		blt_has_flag(t_expression *cmd);
int			blt_one_arg(char const *input, int min, int max, int *out);
void		perror_exit(char *msg, int exit_code);
void		perror_msg_exit(char *msg_start, char *msg_end, int exit_code);
void		msg_exit(char *function, char *error, int exit_code);
int			soft_perror(char *msg, int exit_code);
int			soft_msg(char *function, char *error, int exit_code);
pid_t		exe_command(t_expression *cmd);
char		*get_full_path_cmd(const char *cmd_name, char *search_path);
void		set_all_redirect(t_file *head);
void		set_fd(t_file *file, int change_fd);
void		read_file(t_file *file, int change_fd);
void		write_file(t_file *file, int change_fd);
void		write_append_file(t_file *file, int change_fd);
void		run_all(t_expression *root);
pid_t		run_tree(t_expression *cmd);
pid_t		exe_pipe(t_expression *cmd);
pid_t		exe_and(t_expression *cmd);
pid_t		exe_or(t_expression *cmd);
void		save_close(int *fd);
void		close_files(t_file *head);
void		close_all_files(t_expression *root);
int			env_get_len_key(char *line);
char		**env_get_line_ptr(char *line);
char		*env_get_line_data(char *line);
char		***env_get_ptr(void);
int			env_get_size(char **environment);
void		env_add_line(char *line);
void		env_add_line_data(char *key, char *value);
void		env_remove_line(char *line);
void		env_init(char **input_envp);
void		swap_ptrs(int **a, int **b);
void		save_dup2(int old_fd, int new_fd);
void		save_pipe(int *write_in_pipe, int *read_out_pipe);
char		*save_getcwd(char *buf, size_t size);
void		save_chdir(const char *new_dir);
void		free_split(char **split);
void		gc_init(void);
t_list		*gc_add(void *memory);
void		gc_mode(t_gc_index mode);
void		gc_clear(t_gc_index index);
void		gc_clear_temporary(void);
void		gc_clear_all(void);
char		*gc_substr(char const *string, unsigned int start, size_t length);
char		*gc_strdup(char const *string);
char		*gc_strjoin(char const *s1, char const *s2);
void		*gc_calloc(size_t count, size_t size);
char		*gc_getcwd(void);
void		gc_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		*gc_remove_one(void *remove_ptr);
t_data		*data(void);
int			main(int argc, char **argv, char **envp);
int			is_redirect(t_token *token);
int			is_operator(t_token *token);
int			is_parenthesis(t_token *token);
t_atom		*atom_new();
void		atom_replace_token(t_atom *atom, t_token *token);
int			atom_count_args(t_atom *atom);
void		atom_add_arg(t_atom *atom, t_token *token);
void		atomize(t_tokens *tokens);
t_token		*tok_new(char *content, t_token_type type);
void		tok_add(char *content, t_token_type type, t_tokens *list);
void		tok_delete(t_token *token);
void		tok_join(t_token *first, t_token *second);
void		tok_debug_display(t_tokens *tokens);
void		tok_reset(t_tokens *tokens);
int			tok_is_meta_chararacter(char c);
void		tok_expansion(t_token *token, char *line);
int			tok_make_meta_token(char *position, t_tokens *list);
int			tok_make_word_token(char *position, t_tokens *list);
int			tok_make_space_token(char *position, t_tokens *list);
void		expand(t_tokens *tokens);
void		strip_whitespace(t_tokens *tokens);
void		strip_quotes(t_tokens *tokens);
void		join_quotes(t_tokens *tokens);
void		quote(t_tokens *tokens);
void		split_line(char *line, t_tokens *list);
void		tokenize(char *line);

#endif
