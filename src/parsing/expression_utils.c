/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:36:20 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/28 22:36:30 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
