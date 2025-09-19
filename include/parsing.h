/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:59:30 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/19 17:52:04 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
	TOK_BACKSLASH,
	TOK_ATOM
}	t_token_type;

typedef struct s_token_key
{
	char			*key;
	t_token_type	type;
}	t_token_key;

typedef struct	s_token t_token;

typedef struct	s_token
{
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
	char			*content;
	t_token_type	is_quoted;
}	t_token;

typedef enum e_filetype
{
	FILE_PATH,
	FILE_HEREDOC,
	FILE_PIPE
}	t_filetype;

typedef struct s_file
{
	t_filetype	type;		// type of redirect, pipe, here_doc, actual file
	char		*path;		// path for files to be opened (since cd may be invoked by previous commands)
	int			pipe[2];	// pipes and here_doc
	char		*delimiter;	// for here_doc
}	t_file;

typedef struct s_atom
{
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
	char			*command;
	int				argc;
	char			**args;
	// t_file			*in_files;
	// t_file			*out_files;
}	t_atom;


typedef	struct	s_tokens
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
}	t_tokens;

typedef enum e_expression_operator
{
	OPERATOR_CMD,	// no operator
	OPERATOR_PIPE,	// |
	OPERATOR_AND,	// &&
	OPERATOR_OR,	// ||
}	t_expression_operator;

typedef struct s_expression t_expression;

typedef struct s_expression
{
	t_expression_operator	type;
	t_expression			*parent;	// NULL if root
	t_expression			*first;		// NULL if no first child
	t_expression			*second;	// NULL if no second child
	char					*command;	// command string (first position in args)
	char					**args;		// including command at first position
	t_file					*in_files;	// redirect stdin
	t_file					*out_files;	// redirect out
}	t_expression;

#endif