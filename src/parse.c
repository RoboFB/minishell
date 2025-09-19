/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:49:47 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/19 20:14:49 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	check if the given token is any kind of redirect

*/
int	is_redirect(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_DOUBLE_LESS || token->type == TOK_DOUBLE_GREATER
			|| token->type == TOK_GREATER || token->type == TOK_LESS);
}

int	is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_PIPE || token->type == TOK_AND
			|| token->type == TOK_OR || token->type == TOK_SEMICOLON);
}

int	is_parenthesis(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOK_LEFT_PARENTHESIS
			|| token->type == TOK_RIGHT_PARENTHESIS);
}

t_atom	*atom_new()
{
	t_atom	*atom;

	atom = (t_atom *)gc_calloc(1, sizeof(t_atom));
	atom->type = TOK_ATOM;
	ft_printf("new atom\n");
	
	return (atom);
}

void	atom_replace_token(t_atom *atom, t_token *token)
{
	t_tokens	*tokens;

	tokens = &data()->tokens;
	if (token == tokens->head)
		tokens->head = (t_token *)atom;
	if (token == tokens->tail)
		tokens->tail = (t_token *)atom;
	atom->next = token->next;
	atom->prev = token->prev;
	if (token->next)
		token->next->prev = (t_token *)atom;
	if (token->prev)
		token->prev->next = (t_token *)atom;
	ft_printf("new atom placed\n");
}

int	atom_count_args(t_atom *atom)
{
	int	count;

	count = 0;
	while (atom->args[count])
		count++;
	return (count);
}

// not system call efficient at the moment. Should work though.
void	atom_add_arg(t_atom *atom, t_token *token)
{
	if (!atom->args)
	{
		atom->args = (char **)gc_calloc(2, sizeof(char **));
		atom->args[0] = token->content;
		atom->args[1] = NULL;
	}
	else
	{
		atom->args = (char **)gc_realloc(atom->args, 
			(atom->argc + 1) * sizeof(char **),
			(atom->argc + 2) * sizeof(char **));
		atom->args[atom->argc] = token->content;
		atom->args[atom->argc + 1] = NULL;
	}
	atom->next = token->next;
	token->prev = atom->prev;
	atom->command = atom->args[0];
	atom->argc++;
	return ;
}

// void	atom_add_file(t_atom *, t_token *token)
// {
	
// }

void	atomize(t_tokens *tokens)
{
	t_token	*token;
	t_atom	*atom;

	token = tokens->head;
	atom = atom_new();
	while (token)
	{
		if (token->type == TOK_WORD && !atom->args)
		{
			atom_replace_token(atom, token);
			atom_add_arg(atom, token);
		}
		else if (token->type == TOK_WORD && atom->args)
			atom_add_arg(atom, token);
		else if (is_operator(token))
			atom = atom_new();
		token = token->next;
	}
}

/*	to make an "atom" I need to consider command, arguments and redirects,
	cutting off once I hit an operator ('|', "||", "&&") or parenthesis 
	('(', ')'). Parenthesis not followed by a redirect or command (word) are in
	the wrong place. Unclosed parentheses should not be tolerated.

	To produce useable results I need to make scalable lists of arguments and 
	files for redirection. It may look something like this:

	char *cmd   e. g. 	"echo"
	char **args e. g.	"hello", "world", NULL
	t_list *in	e. g.	HERE_DOC -> "test.txt" -> NULL
	t_list *out e. g.	"test.txt"::stdout -> "test2.txt"::stderr -> NULL

	for file lists, latest wins. At least that is the current working theory.

	These atoms can then be interpreted into an abstract syntax tree using the
	precedence produced by the operators [|] > [&&] = [||], parentheses and 
	left to right reading direction.
	e. g.:

	cat test.txt | grep $USER && printf "contains" || printf "does not contain"
	\_atom_____/   \_atom___/    \_atom__________/    \_atom_________________/
	 \_pipe_expression_____/                    /                           /
	  \_and_expression_________________________/                           /
	   \_or_expression____________________________________________________/

	or ______
	|        |
	and___   b
	|     |
	pipe  b
	| |
	a b

	cat test.txt | grep $USER && (printf "contains" || printf "does not contain")
	\_atom_____/   \_atom___/     \_atom__________/    \_atom__________________/
	 \_pipe_expression_____/       \_or_expression____________________________/
	  \_and_expression_______________________________________________________/

	and ___
	|      |
	pipe   or
	| |    | |
	a b    a b

	expression results are treated as atoms for their parent expressions, 
	either for piping or if/else short-circuiting

*/
