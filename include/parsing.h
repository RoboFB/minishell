/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:59:30 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/24 18:59:41 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "public_struct.h"

typedef struct s_file t_file;

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

typedef struct s_file t_file;

typedef struct s_atom
{
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
	int				argc;
	char			**args;
	t_file			*files;	// last has priority (per io-channel)
}	t_atom;

typedef struct s_bind
{
	int	left;
	int	right;
}	t_bind;

#endif