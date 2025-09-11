/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:59:40 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/11 18:39:52 by modiepge         ###   ########.fr       */
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
	GC_EXPANSION,
	GC_PARSING,
	GC_EXECUTION,
	GC_PERSISTENT
}	t_gc_index;

typedef union	u_gc_book
{
	struct
	{
		t_list	*lexing;
		t_list	*expansion;
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
void		gc_init(void);
t_list		*gc_add(void *memory);
void		gc_mode(t_gc_index mode);
void		gc_clear(t_gc_index index);
void		gc_clear_all(void);
char		*gc_substr(char const *string, unsigned int start, size_t length);
char		*gc_strdup(char const *string);
void		*gc_calloc(size_t count, size_t size);
t_data		*data(void);
int			main(int argc, char **argv, char **envp);
t_token		*tok_new(char *content, t_token_type type);
void		tok_add(char *content, t_token_type type);
void		tok_debug_display(t_tokens *tokens);
void		tok_reset(t_tokens *tokens);
int			tok_is_meta_chararacter(char c);
int			tok_make_meta_token(char *position);
int			tok_make_word_token(char *position);
int			tok_make_space_token(char *position);
void		tokenize(char *line);

#endif
