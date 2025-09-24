/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   public_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:50:53 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/23 19:56:56 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUBLIC_STRUCT_H
# define PUBLIC_STRUCT_H

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
	t_list	*lists[4];
}	t_gc_book;

typedef struct	s_token t_token;

typedef	struct	s_tokens
{
	t_token	*head;
	t_token	*tail;
	size_t	size;
}	t_tokens;

typedef struct s_expression t_expression;

typedef struct	s_data
{
	char**			envp;
	char*			line;
	t_tokens		tokens;
	t_tokens		expansion;
	t_expression	*ast;
	t_gc_index		gc_mode;
	t_gc_book		gc_book;
}	t_data;

typedef enum e_filetype
{
	PATH_STDIN_READ,
	PATH_STDOUT_WRITE,
	PATH_STDERR_WRITE,
	PATH_STDOUT_WRITE_APPEND,
	PATH_STDERR_WRITE_APPEND,
	FD_HEREDOC_READ,
	FD_PIPE_READ,
	FD_PIPE_WRITE
}	t_filetype;

typedef struct s_file t_file;

typedef struct s_file
{
	t_filetype	type;		// type of redirect, pipe, here_doc, actual file
	char		*path;		// path for files to be opened (since cd may be invoked by previous commands)
	int			fd;			// pipes and here_doc // init -1/ not used
	t_file		*next;
}	t_file;

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
	char					*name;		// command string (first position in args)
	char					**args;		// including command at first position
	t_file					*files;		// last has priority (per io-channel)
}	t_expression;

# endif