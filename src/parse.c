/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:49:47 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/24 19:01:00 by modiepge         ###   ########.fr       */
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
	gc_mode(GC_LEXING);
	atom = (t_atom *)gc_calloc(1, sizeof(t_atom));
	atom->type = TOK_ATOM;
	ft_debugf(1, "atomize: new atom\n");
	return (atom);
}

void	atom_feed(t_atom **atom)
{
	t_tokens	*tokens;
	t_token		**food;

	if (!(*atom))
		return ;
	tokens = &data()->tokens;
	food = &(*atom)->next;
	if (*food == tokens->tail)
		tokens->tail = (t_token *)atom;
	if ((*food) && (*food)->next)
	{
		(*food)->next->prev = (t_token *)(*atom);
		(*atom)->next = (*food)->next;
	}
	else
		(*atom)->next = NULL;
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
	ft_debugf(1, "atomize: atom placed\n");
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
	gc_mode(GC_PARSING);
	if (!atom->args)
	{
		atom->args = (char **)gc_calloc(2, sizeof(char *));
		atom->args[0] = gc_strdup(token->content);
		atom->args[1] = NULL;
	}
	else
	{
		gc_realloc((void **)&atom->args, atom->argc + 1, atom->argc + 2, sizeof(char *));
		atom->args[atom->argc] = gc_strdup(token->content);
		atom->args[atom->argc + 1] = NULL;
	}
	atom->next = token->next;
	token->prev = atom->prev;
	atom->argc++;
	ft_debugf(1, "atomize: added argument\n");
}

void	atom_add_file(t_atom *atom, t_token **token)
{
	gc_mode(GC_PARSING);
	get_redirect(atom, token);
	atom_feed(&atom);
	atom_feed(&atom);
	return ;
}

void	atomize(t_tokens *tokens)
{
	t_token	*token;
	t_atom	*atom;

	token = tokens->head;
	atom = atom_new();
	atom->next = token;
	token->prev = (t_token*)atom;
	token = (t_token*)atom;
	token = token->next;
	while (token)
	{
		ft_debugf(1, "atomize: iteration\n");
		if (token->type == TOK_WORD && !atom->args)
		{
			atom_replace_token(atom, token);
			atom_add_arg(atom, token);
		}
		else if (is_redirect(token))
			atom_add_file(atom, &token);
		else if (token->type == TOK_WORD && atom->args)
			atom_add_arg(atom, token);
		else if (is_operator(token))
			atom = atom_new();
		if (token)
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

t_expression	*atom_to_expression(t_atom *atom)
{
	t_expression	*expression;

	if (!atom)
		return (NULL);
	gc_mode(GC_PARSING);
	expression = (t_expression *)gc_calloc(1, sizeof(t_expression));
	expression->type = OPERATOR_CMD;
	expression->args = atom->args;
	expression->files = atom->files;
	expression->name = atom->args[0];
	return (expression);
}

t_expression	*make_expression(t_expression_operator operator, t_expression *first, t_expression *second)
{
	t_expression	*expression;

	gc_mode(GC_PARSING);
	expression = (t_expression *)gc_calloc(1, sizeof(t_expression));
	expression->type = operator;
	expression->first = first;
	expression->second = second;
	return (expression);
}

t_expression_operator	expression_type(t_token_type type)
{
	if (type == TOK_AND)
		return (OPERATOR_AND);
	if (type == TOK_OR)
		return (OPERATOR_OR);
	if (type == TOK_PIPE)
		return (OPERATOR_PIPE);
	return (OPERATOR_CMD);
}

t_bind	*binding_power(t_token *token)
{
	static const	t_bind binding_power[6] = {{30,31}, {20,21}, {20,21}, {10,0}, {0,10}};
	if (token->type == TOK_PIPE)
		return ((t_bind *)&binding_power[0]);
	if (token->type == TOK_AND)
		return ((t_bind *)&binding_power[1]);
	if (token->type == TOK_OR)
		return ((t_bind *)&binding_power[2]);
	ft_fprintf(2, "minishell: syntax error at \"%s\"\n", token->content);
	exit(0);
}

t_expression	*parse_expression(t_token *token, const int minimum_binding)
{
	t_expression			*first;
	t_expression			*second;
	t_expression_operator	operator;
	t_bind					*binding;

	if (!token)
		return (NULL);
	if (token->type == TOK_ATOM)
		first = atom_to_expression((t_atom *)token);
	else if (token->type == TOK_LEFT_PARENTHESIS)
	{
		first = parse_expression(token->next, 0);
	}
	else
		return (NULL);
	operator = 0;
	while (token)
	{
		token = token->next;
		if (!token)
			break ;
		else if (token->type == TOK_RIGHT_PARENTHESIS)
			break ;
		else if (is_operator(token))
		{
			operator = expression_type(token->type);
			binding = binding_power(token);
		}
		if (binding && binding->left < minimum_binding)
			break ;
		token = token->next;
		second = parse_expression(token, binding->right);
		first = make_expression(operator, first, second);
		if (first->first)
			first->first->parent = first;
		if (first->second)
			first->second->parent = first;
	}
	return (first);
}

void	debug_tree(t_expression *expression, char *side, bool op)
{
	const char	*debug_type[4] = {"OPERATOR_CMD", "OPERATOR_PIPE", "OPERATOR_AND",\
		"OPERATOR_OR"};
	int			index;
	t_file		*file;

	if (!expression)
		return ;
	if (expression && expression->type != OPERATOR_CMD)
	{
		if (expression->first)
			debug_tree(expression->first, "first", true);
		if (expression->first && expression->first->type != OPERATOR_CMD 
			&& expression->second && expression->second->type != OPERATOR_CMD)
			ft_debugf(77,  "%s:\n", debug_type[expression->type]);
		if (expression->second)
			debug_tree(expression->second, "second", 
				(expression->first && expression->first->type != OPERATOR_CMD));
	}
	else if (expression && expression->type == OPERATOR_CMD)
	{
		index = 0;
		if (expression->parent && op)
			ft_debugf(77,  "%s\t%s: ", debug_type[expression->parent->type], side);
		else
			ft_debugf(77,  "\t\t%s: ", side);
		ft_debugf(77,  "args: ");
		while (expression && expression->args[index])
			ft_debugf(77,  "%s ", expression->args[index++]);
		if (expression && expression->files)
		{
			ft_debugf(77,  "files: ");
			file = expression->files;
		}
		else
		{
			file = NULL;
		}
		while (expression && file)
		{
			ft_debugf(77,  "%s ", file->path);
			file = file->next;
		}
		ft_debugf(77,  "\n");
	}
}

void	list_to_tree(void)
{
	t_tokens		*tokens;
	t_token			*token;
	t_expression	**ast;

	tokens = &data()->tokens;
	ast = &data()->tree_root;
	token = tokens->head;
	gc_mode(GC_PARSING);
	*ast = parse_expression(token, 0);
	gc_clear(GC_LEXING);
	debug_tree(*ast, "root", 0);
}

