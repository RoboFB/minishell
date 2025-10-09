/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:49:47 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/09 16:47:09 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	the blueprint for atoms has to change, since I need useable tokens during 
	execution to expand, strip and or join. This probably includes file 
	redirects. So, I am going to gather the tokens ahead, after and between 
	logic operators as previously, add them as is to the expression and then 
	punch them into their slots during execution, appropriately expanded etc.
*/
t_expression	*token_to_expression(t_token *token)
{
	t_expression	*expression;

	if (!token || (token && token->type != TOK_ATOM))
		return (NULL);
	expression = (t_expression *)gc_calloc(1, sizeof(t_expression));
	expression->type = OPERATOR_CMD;
	expression->collection = token->collection;
	expression->args = NULL;
	expression->argc = 0;
	expression->files = NULL;
	expression->name = NULL;
	return (expression);
}

t_token	*token_next(t_token **token)
{
	t_token	*current;

	if (!token || !*token)
		return (NULL);
	current = *token;
	*token = (*token)->next;
	return (current);
}

t_token	*token_peek(t_token **token)
{
	if (!token)
		return (NULL);
	return (*token);
}

t_expression *nud(t_token **token)
{
	t_token			*next;
	t_expression	*inner;
	t_token			*peek;

	next = token_peek(token);
	inner = NULL;
	if (!next)
		return (NULL);
	if (next->type == TOK_ATOM)
	{
		token_next(token);
		return (token_to_expression(next));
	}
	if (next->type == TOK_LEFT_PARENTHESIS)
	{
		token_next(token);
		inner = parse_expression(token, 0);
		peek = token_peek(token);
		if (!peek || peek->type != TOK_RIGHT_PARENTHESIS)
		{
			ft_fprintf(2, "minishell: syntax error, expected ')'");
			return (NULL);
		}
		token_next(token);
		return (inner);
	}
	return (NULL);
}

t_expression *led(t_token **token, t_expression *first, t_token *operator)
{
	t_expression_operator	op;
	t_bind					*binding;
	t_expression			*second;
	t_expression			*new;

	op = expression_type(operator->type);
	binding = binding_power(operator);
	second = parse_expression(token, binding->right);
	if (!second || !binding)
		return (NULL);
	new = make_expression(op, first, second);
	if (new && new->type == OPERATOR_PIPE)
	{
		// file add / add front, pipe (empty)
	}
	if (new->first)
		first->parent = new;
	if (new->second)
		second->parent = new;
	return (new);
}


t_expression *parse_expression(t_token **token, const int minimum_binding)
{
	t_expression	*first;
	t_expression	*new;
	t_token			*next;
	t_bind			*binding;

	if (!token || !*token)
		return (NULL);
	first = nud(token);
	if (!first)
		return (NULL);
	while (1)
	{
		next = token_peek(token);
		if (!next || next->type == TOK_RIGHT_PARENTHESIS)
			break ;
		binding = binding_power(next);
		if (!binding || binding->left < 0 || binding->left < minimum_binding)
			break ;
		token_next(token);
		new = led(token, first, next);
		if (!new)
			return (NULL);
		first = new;
	}
	return (first);
}


// t_expression	*parse_expression(t_token *token, const int minimum_binding)
// {
// 	t_expression			*first;
// 	t_expression			*second;
// 	t_expression_operator	operator;
// 	t_bind					*binding;

// 	if (!token)
// 		return (NULL);
// 	if (token->type == TOK_ATOM)
// 		first = atom_to_expression((t_atom *)token);
// 	else if (token->type == TOK_LEFT_PARENTHESIS)
// 	{
// 		first = parse_expression(token->next, 0);
// 	}
// 	else
// 		return (NULL);
// 	operator = 0;
// 	while (token)
// 	{
// 		token = token->next;
// 		if (!token)
// 			break ;
// 		else if (token->type == TOK_RIGHT_PARENTHESIS)
// 			break ;
// 		else if (is_operator(token))
// 		{
// 			operator = expression_type(token->type);
// 			binding = binding_power(token);
// 		}
// 		if (!token || (binding && binding->left < minimum_binding))
// 			break ;
// 		token = token->next;
// 		second = parse_expression(token, binding->right);
// 		first = make_expression(operator, first, second);
// 		if (first->first)
// 			first->first->parent = first;
// 		if (first->second)
// 			first->second->parent = first;
// 	}
// 	return (first);
// }

void	list_to_tree(void)
{
	t_tokens		*tokens;
	t_token			*token;
	t_expression	**ast;

	tokens = &data()->tokens;
	ast = &data()->tree_root;
	token = tokens->head;
	*ast = parse_expression(&token, 0);
	if (*ast)
		debug_tree(*ast);
}
