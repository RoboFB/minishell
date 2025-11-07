/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:50:53 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/07 15:31:46 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUBLIC_STRUCT_H
# define PUBLIC_STRUCT_H

/* 
******************** TOKENS **********************
token type,  token,  tokens
 */

typedef enum e_token_type
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
	TOK_BACKSLASH,
	TOK_QUESTION,
	TOK_ATOM
}	t_token_type;

typedef struct s_token			t_token;
typedef struct s_tokens
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
}	t_tokens;

typedef struct s_file			t_file;
typedef struct s_token
{
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
	char			*content;
	t_tokens		collection;
	t_token_type	is_quoted;
	t_file			*files;
	unsigned int	id;
}	t_token;

// helper
typedef struct s_token_key
{
	char			*key;
	t_token_type	type;
}	t_token_key;

typedef struct s_bind
{
	int	left;
	int	right;
}	t_bind;

/* 
******************** EXPRESSION **********************
 */

// file type for redirects
typedef enum e_filetype
{
	NOT_SET = -1,
	PATH_STDIN_READ,
	PATH_STDOUT_WRITE,
	PATH_STDERR_WRITE,
	PATH_STDOUT_WRITE_APPEND,
	PATH_STDERR_WRITE_APPEND,
	FD_HEREDOC_READ,
	FD_PIPE_READ,
	FD_PIPE_WRITE
}	t_filetype;

/*	linked list files
	@param type pipes and here_doc // init -1/ not used
	@param path for files to be opened 
				(since cd may be invoked by previous commands)
	@param fd of redirect, pipe, here_doc, actual file
*/
typedef struct s_file
{
	t_filetype	type;
	char		*path;
	int			fd;
	t_tokens	collection;
	t_file		*next;
}	t_file;

typedef enum e_expression_operator
{
	OPERATOR_CMD,
	OPERATOR_PIPE,
	OPERATOR_AND,
	OPERATOR_OR,
}	t_expression_operator;

typedef struct s_expression		t_expression;

typedef struct s_expression
{
	t_expression_operator	type;
	t_expression			*parent;
	t_expression			*first;
	t_expression			*second;
	char					*name;
	char					**args;
	int						argc;
	t_file					*files;
	t_tokens				collection;
}	t_expression;

// garbage collector

typedef enum e_gc_index
{
	GC_WORKING,
	GC_TEMPORARY,
	GC_PERSISTENT
}	t_gc_index;

typedef union u_gc_book
{
	struct
	{
		t_list	*lexing;
		t_list	*parsing;
		t_list	*execution;
		t_list	*persistent;
	};
	t_list	*lists[4];
}	t_gc_book;

// 1.	exit codes

typedef enum e_exit_code
{
	EXIT_OK = EXIT_SUCCESS,
	EXIT_GENERAL_ERROR = EXIT_FAILURE,
	EXIT_SYNTAX_ERROR = 2,
	EXIT_BLT_CMD_NOT_EXECUTABLE = 126,
	EXIT_BLT_CMD_NOT_FOUND = 127,
	EXIT_SIGNAL_BASE = 128,
	EXIT_MAX = 255,
}	t_exit_code;

// main data static struct
typedef struct s_data
{
	char			**envp;
	char			*line;
	t_tokens		tokens;
	t_tokens		expansion;
	t_gc_index		gc_mode;
	t_gc_book		gc_book;
	t_expression	*tree_root;
	int				last_exit_code;
	pid_t			pid;
	pid_t			animation;
	int				animation_variant;
	int				animation_enabled;
}	t_data;

#endif
