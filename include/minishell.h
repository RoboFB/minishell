/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:59:40 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/17 20:26:26 by rgohrig          ###   ########.fr       */
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

typedef enum	e_token_type
{
	TOK_WORD,
	TOK_WHITESPACE,
	TOK_PIPE,
	TOK_LEFT_PARENTHESIS,
	TOK_RIGHT_PARENTHESIS,
	TOK_LESS,
	TOK_DOUBLE_LESS,
	TOK_GREATER,
	TOK_DOUBLE_GREATER,
	TOK_QUOTE,
	TOK_DOUBLE_QUOTE,
	TOK_AND,
	TOK_OR,
	TOK_VARIABLE,
	TOK_WILDCARD,
	TOK_AMPERSAND,
	TOK_SEMICOLON,
	TOK_BACKSLASH
}	t_token_type;

typedef struct s_token_key
{
	char			*key;
	t_token_type	type;
}	t_token_key;

typedef	enum	e_gc_index
{
	GC_LEXING,
	GC_PARSING,
	GC_EXECUTION,
	GC_PERSISTENT
}	t_gc_index;

typedef union	u_gc_book
{
	struct
	{
		t_list	*lexing;
		t_list	*parsing;
		t_list	*execution;
		t_list	*persistent;
	};
	t_list	*lists[5];
}	t_gc_book;

typedef struct	s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef	struct	s_tokens
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
}	t_tokens;

typedef struct	s_data
{
	char**		envp;
	char*		line;
	t_tokens	tokens;
	t_tokens	expansion;
	t_gc_index	gc_mode;
	t_gc_book	gc_book;
}	t_data;

// auto
t_token		*tok_new(char *content, t_token_type type);
void		tok_add(char *content, t_token_type type);
void		tok_delete(t_token *token);
void		tok_join(t_token *first, t_token *second);
void		tok_debug_display(t_tokens *tokens);
void		tok_reset(t_tokens *tokens);
int			tok_is_meta_chararacter(char c);
int			tok_make_meta_token(char *position);
int			tok_make_word_token(char *position);
int			tok_make_space_token(char *position);
void		expand(t_tokens *tokens);
void		quote(t_tokens *tokens);
void		tokenize(char *line);
void		perror_exit(char *msg, int exit_code);
void		msg_exit(char *function, char* error, int exit_code);
void		exe_command(t_command *cmd);
char		*get_full_path_cmd(const char *cmd_name, char *search_path);
void		start_command(t_command *cmd);
void		child_pipe(t_command *command);
void		redirect_input(t_command *command);
void		redirect_output(t_command *command);
void		redirect_error(t_command *command);
void		redirect_append(t_command *command);
void		redirect_here_doc(t_command *command);
void		child_and(t_command *command);
void		child_or(t_command *command);
void		blt_cd(t_command *cmd);
void		blt_pwd(t_command *cmd);
void		blt_echo(t_command *cmd);
void		blt_unset(t_command *cmd);
void		blt_env(t_command *cmd);
void		blt_exit(t_command *cmd);
void		blt_export(t_command *cmd);
void		try_builtin(t_command *command);
void		gc_init(void);
t_list		*gc_add(void *memory);
void		gc_mode(t_gc_index mode);
void		gc_clear(t_gc_index index);
void		gc_clear_all(void);
char		*gc_substr(char const *string, unsigned int start, size_t length);
char		*gc_strdup(char const *string);
char		*gc_strjoin(char const *s1, char const *s2);
void		*gc_calloc(size_t count, size_t size);
void		gc_realloc(void **change_ptr, size_t old, size_t new, size_t size);
void		*gc_remove_one(void *remove_ptr);
int			env_get_len_key(char *line);
char		**env_get_line_ptr(char *line);
char		*env_get_line_data(char *line);
char		***env_get_ptr(void);
int			env_get_size(char **environment);
void		env_add_line(char *line);
void		env_remove_line(char *line);
void		env_init(char **input_envp);
t_data		*data(void);
int			main(int argc, char **argv, char **envp);
void		swap_ptrs(int **a, int **b);
void		save_close(int fd);
void		save_dup2(int old_fd, int new_fd);
void		save_pipe(int *one_pipe);
void		close_one_pip(int *pipe);
void		free_split(char **split);

#endif
