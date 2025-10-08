/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:59:40 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/29 16:55:21 by modiepge         ###   ########.fr       */
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
# include <stdio.h>		// printf, perror
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill
// # include <sys/ioctl.h>	// ioctl
# include <stdbool.h>	// bool type (is not a function)
# include <limits.h>	// INT_MAX, PATH_MAX (is not a function)

# include "libft.h"
# include "libft_printf.h"
# include "libft_styles.h"
# include "execution.h"
# include "public_struct.h"
# include "parsing.h"


// auto
int			blt_one_arg(char const *input, int min, int max, int *out);
int			blt_count_args(t_expression *cmd);
bool		blt_has_flag(t_expression *cmd);
void		blt_cd(t_expression *cmd);
int			blt_cd_error_check(t_expression *cmd);
char		*blt_cd_get_new_dir(t_expression *cmd);
void		blt_echo(t_expression *cmd);
bool		h_is_n_flag(char *str);
void		blt_env(t_expression *cmd);
void		blt_exit(t_expression *cmd);
void		blt_export(t_expression *cmd);
void		blt_pwd(t_expression *cmd);
void		blt_unset(t_expression *cmd);
void		run_builtin(t_expression *command);
bool		is_builtin(t_expression *command);
char		*get_full_path_cmd(const char *cmd_name, char *search_path);
void		save_close(int *fd);
void		close_files(t_file *head);
void		close_all_files(t_expression *root);
pid_t		exe_command(t_expression *cmd);
bool		is_single_command(t_expression *cmd);
void		run_builtin_in_main(t_expression *cmd);
void		run_comand(t_expression *cmd);
void		exit_shell(t_exit_code exit_code);
void		perror_exit(char *msg, t_exit_code exit_code);
void		perror_msg_exit(char *msg_start, char *msg_end, t_exit_code exit_code);
void		msg_exit(char *function, char *error, t_exit_code exit_code);
void		msg_error(char *function, char *error);
void		switch_exit(t_expression *cmd, t_exit_code exit_code);
void		run_all(void);
pid_t		run_tree(t_expression *cmd);
pid_t		exe_pipe(t_expression *cmd);
pid_t		exe_and(t_expression *cmd);
pid_t		exe_or(t_expression *cmd);
void		wait_and_set_exit_code(pid_t pid);
void		set_all_redirect(t_file *head);
void		set_fd(t_file *file, int change_fd);
void		read_file(t_file *file, int change_fd);
void		write_file(t_file *file, int change_fd);
void		write_append_file(t_file *file, int change_fd);
int			env_get_len_key(char *line);
char		**env_get_line_ptr(char *line);
char		*env_get_line_data(char *line);
char		***env_get_ptr(void);
int			env_get_size(char **environment);
void		env_add_line(char *line);
void		env_add_line_data(char *key, char *value);
void		env_remove_line(char *line);
void		env_init(char **input_envp);
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
void		save_dup2(int old_fd, int new_fd);
int			save_dup(int copy_fd);
void		save_pipe(int *write_in_pipe, int *read_out_pipe);
char		*save_getcwd(char *buf, size_t size);
void		save_chdir(const char *new_dir);
pid_t		save_fork(void);
void		tok_debug_display(t_tokens *tokens);
void		debug_tree(t_expression *root);
void		expression_add_arg(t_expression *atom, t_token *token);
void		expression_add_file(t_expression *atom, t_token **token);
void		resolve(t_expression *expression);
void		parse(char *line, t_tokens *list);
t_token		*atomize(t_token **token);
void		contract(t_tokens *list);
void		tokenize(char *line, t_tokens *list);
t_token		*tok_new(char *content, t_token_type type);
void		tok_add(t_token *new, t_tokens *list);
void		tok_delete(t_token **token, t_tokens *list);
void		tok_join(t_token *first, t_token *second, t_tokens *list);
void		list_reset(t_tokens *tokens);
int			token_is_redirect(t_token *token);
int			token_is_operator(t_token *token);
int			token_is_parenthesis(t_token *token);
int			token_is_separator(t_token *token);
int			is_meta_chararacter(char c);
void		tok_expansion(t_token *token, char *line);
void		expand(t_tokens *tokens);
int			tok_make_meta_token(char *position, t_tokens *list);
int			tok_make_word_token(char *position, t_tokens *list);
int			tok_make_space_token(char *position, t_tokens *list);
void		line_split(char *line, t_tokens *list);
void		strip_quotes(t_tokens *tokens);
void		join_quotes(t_tokens *list);
void		quote(t_tokens *list);
void		strip_whitespace(t_tokens *tokens);
void		heredoc_expand(int fd, char *line);
void		heredoc_in(t_expression *atom, t_token **token);
t_file		*redirect_out(t_expression *atom, t_token **token);
t_file		*redirect_in(t_expression *atom, t_token **token);
t_file		*file_last(t_file *files);
t_file		*file_add_front(t_file **files);
t_file		*file_add(t_file **files);
t_filetype		get_redirect(t_expression *atom, t_token **token);
t_expression		*make_expression(t_expression_operator operator, t_expression *first, t_expression *second);
t_expression_operator		expression_type(t_token_type type);
t_bind		*binding_power(t_token *token);
t_expression		*token_to_expression(t_token *token);
t_token		*token_next(t_token **token);
t_token		*token_peek(t_token **token);
t_expression		*nud(t_token **token);
t_expression		*led(t_token **token, t_expression *first, t_token *operator);
t_expression		*parse_expression(t_token **token, const int minimum_binding);
void		list_to_tree(void);
t_data		*data(void);
int			main(int argc, char **argv, char **envp);

#endif
