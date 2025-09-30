/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:17:24 by modiepge          #+#    #+#             */
/*   Updated: 2025/09/29 16:44:40 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_debug_display(t_tokens *tokens)
{
	t_token		*token;
	const char	*debug_type[18] = {"TOK_WORD", "TOK_WHITESPACE", "TOK_PIPE",
		"TOK_LEFT_PARENTHESIS", "TOK_RIGHT_PARENTHESIS", "TOK_LESS",
		"TOK_DOUBLE_LESS", "TOK_GREATER", "TOK_DOUBLE_GREATER", "TOK_QUOTE",
		"TOK_DOUBLE_QUOTE", "TOK_AND", "TOK_OR", "TOK_VARIABLE",
		"TOK_WILDCARD", "TOK_AMPERSAND", "TOK_SEMICOLON", "TOK_BACKSLASH"};
	int	arg;
	t_atom *atom;
	t_file *file;

	token = tokens->head;
	ft_debugf(2, "minishell: debug -- display tokens\n\n");
	while (token)
	{
		if (token->type != TOK_ATOM)
			ft_debugf(2, "token: \t%s is %s\n", token->content, debug_type[token->type]);
		else
		{
			atom = (t_atom *)token;
			ft_debugf(2, "atom:\targs[%d]: %s ", atom->argc, atom->args[0]);
			arg = 0;
			while (atom->args[arg + 1])
			{
				ft_debugf(2, "%s ", atom->args[arg + 1]);
				arg++;
			}
			file = atom->files;
			if (file)
				ft_debugf(2, "\n     \tfiles: ");
			while (file)
			{
				ft_debugf(2, "%s ", file->path, file->type);
				file = file->next;
			}
			ft_debugf(2, "\n");
		}
		token = token->next;
	}
	ft_debugf(2, "\n");
}

// void	debug_tree(t_expression *expression, char *side, bool op)
// {
// 	const char	*debug_type[4] = {"OPERATOR_CMD", "OPERATOR_PIPE", "OPERATOR_AND",\
// 		"OPERATOR_OR"};
// 	int			index;
// 	t_file		*file;

// 	if (!expression)
// 		return ;
// 	if (expression && expression->type != OPERATOR_CMD)
// 	{
// 		if (expression->first)
// 			debug_tree(expression->first, "first", true);
// 		if (expression->first && expression->first->type != OPERATOR_CMD
// 			&& expression->second && expression->second->type != OPERATOR_CMD)
// 			ft_debugf(77,  "%s:\n", debug_type[expression->type]);
// 		if (expression->second)
// 			debug_tree(expression->second, "second",
// 				(expression->first && expression->first->type != OPERATOR_CMD));
// 	}
// 	else if (expression && expression->type == OPERATOR_CMD)
// 	{
// 		index = 0;
// 		if (expression->parent && op)
// 			ft_debugf(77,  "%s\t%s: ", debug_type[expression->parent->type], side);
// 		else
// 			ft_debugf(77,  "\t\t%s: ", side);
// 		ft_debugf(77,  "args: ");
// 		while (expression && expression->args && expression->args[index])
// 			ft_debugf(77,  "%s ", expression->args[index++]);
// 		if (expression && expression->files)
// 		{
// 			ft_debugf(77,  "files: ");
// 			file = expression->files;
// 		}
// 		else
// 		{
// 			file = NULL;
// 		}
// 		while (expression && file)
// 		{
// 			ft_debugf(77,  "%s ", file->path);
// 			file = file->next;
// 		}
// 		ft_debugf(77,  "\n");
// 	}
// }

static void make_under_prefix(char *out, size_t out_sz, const char *prefix, bool last) {
	const int n = snprintf(out, out_sz, "%s%s", prefix, last ? "   " : "│  "); // todo: remove or replace/refactor
	if (n < 0 || (size_t)n >= out_sz) {
        if (out_sz)
			out[out_sz - 1] = '\0';
    }
}

static const char *operator_to_str(t_expression_operator op) {
    static const char *typestring[] = {"CMD", "PIPE", "AND", "OR"};
    if ((int)op >= 0 && (int)op < 4)
		return (typestring[op]);
    return ("???");
}

static const char *filetype_to_str(t_filetype type)
{
    static const char *typestring[8] = {
        "< stdin", "> stdout", "2> stderr", ">> stdout",
        "2>> stderr", "<< heredoc", "< pipe", "> pipe"
    };
    if ((int)type >= 0 && (int)type < 8)
		return (typestring[type]);
    return ("???");
}

static void debug_args_aligned(const char *prefix)
{
    ft_debugf(77, "%s", prefix);
    ft_debugf(77, "  args:  ");
}

static void debug_files_aligned(const char *prefix)
{
    ft_debugf(77, "%s", prefix);
    ft_debugf(77, "  files: ");
}

static void debug_args(char **args)
{
	int index;

	index = 0;
    if (!args || !args[0])
	{
		ft_debugf(77, "\n");
		return;
	}
    while (args[index]) {
        ft_debugf(77, "%s%s", args[index], args[index + 1] ? " " : "");
		index++;
    }
    ft_debugf(77, "\n");
}

static void debug_files(t_file *file)
{
    if (!file)
	{
		ft_debugf(77, "\n");
		return;
	}
    while (file) {
        if (file->path)
			ft_debugf(77, "%s \"%s\"", filetype_to_str(file->type), file->path);
        else
			ft_debugf(77, "%s fd=%d", filetype_to_str(file->type), file->fd);
        if (file && file->next)
			ft_debugf(77, " ");
		file = file->next;
    }
    ft_debugf(77, "\n");
}

static void debug_node(const t_expression *node)
{
    if (!node)
		return;
    ft_debugf(77, "%s", operator_to_str(node->type));
    if (node->type == OPERATOR_CMD && node->name)
        ft_debugf(77, " name \"%s\"", node->name);
}

static int child_count(const t_expression *a, const t_expression *b)
{
	return (2 - !a - !b);
}

static void debug_tree_inner(const t_expression *node, const char *prefix, bool last)
{
	char		next_prefix[1024];
	const int	total = child_count(node->first, node->second);
	int			seen;

	seen = 0;
    if (!node)
		return;
    ft_debugf(77, "%s%s", prefix, last ? "└─ " : "├─ ");
    debug_node(node);
    ft_debugf(77, "\n");
    make_under_prefix(next_prefix, sizeof next_prefix, prefix, last);
    if (node->type == OPERATOR_CMD) {
        debug_args_aligned(next_prefix);
        debug_args(node->args);
        debug_files_aligned(next_prefix);
        debug_files(node->files);
        return;
    }
    if (node->first)  debug_tree_inner(node->first,  next_prefix, (++seen == total));
    if (node->second) debug_tree_inner(node->second, next_prefix, (++seen == total));
}

void debug_tree(t_expression *root)
{
	const int	total = child_count(root->first, root->second);
	int			seen;

	seen = 0;
    if (!root)
	{
		ft_debugf(77, "(empty)\n");
		return;
	}
    debug_node(root);
    ft_debugf(77, "\n");
    if (root->type == OPERATOR_CMD) {
        ft_debugf(77, "   ");
        debug_args_aligned("");
        debug_args(root->args);
        ft_debugf(77, "   ");
        debug_files_aligned("");
        debug_files(root->files);
        return;
    }
    if (root->first)  debug_tree_inner(root->first,  "", (++seen == total));
    if (root->second) debug_tree_inner(root->second, "", (++seen == total));
}
