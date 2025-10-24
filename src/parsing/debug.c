/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modiepge <modiepge@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:17:24 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/24 16:20:10 by modiepge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_debug_display(t_tokens *tokens)
{
	t_token		*token;
	t_token		*subtoken;
	const char	*debug_type[20] = {"TOK_WORD", "TOK_WHITESPACE", "TOK_PIPE",
		"TOK_LEFT_PARENTHESIS", "TOK_RIGHT_PARENTHESIS", "TOK_LESS",
		"TOK_DOUBLE_LESS", "TOK_GREATER", "TOK_DOUBLE_GREATER", "TOK_QUOTE",
		"TOK_DOUBLE_QUOTE", "TOK_AND", "TOK_OR", "TOK_VARIABLE",
		"TOK_WILDCARD", "TOK_AMPERSAND", "TOK_SEMICOLON", "TOK_BACKSLASH", "TOK_QUESTION", "TOK_ATOM"};

	token = tokens->head;
	ft_debugf(2, "minishell: debug -- display tokens\n\n");
	while (token)
	{
		if (token && token->type != TOK_ATOM)
			ft_debugf(2, "token:\t %5s is \t%s (quote: %d)\n", token->content, debug_type[token->type], token->is_quoted);
		else if (token)
		{
			ft_debugf(2, "token is\t\t%s\n", debug_type[token->type]);
			subtoken = token->collection.head;
			while (subtoken)
			{
				ft_debugf(2, "--token: %5s is \t%s (quote: %d)\n", subtoken->content, debug_type[subtoken->type], subtoken->is_quoted);
				subtoken = subtoken->next;
			}
		}
		token = token->next;
	}
	ft_debugf(2, "\n");
}

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
    static const char *typestring[10] = {
        "PATH_STDIN_READ", "PATH_STDOUT_WRITE", "PATH_STDERR_WRITE", "PATH_STDOUT_WRITE_APPEND",
        "PATH_STDERR_WRITE_APPEND", "FD_HEREDOC_READ", "FD_PIPE_READ", "FD_PIPE_WRITE"
    };
    if ((int)type >= 0 && (int)type <9)
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
			ft_debugf(77, "type: %s path: \"%s\"", filetype_to_str(file->type), file->path);
        else
			ft_debugf(77, "type: %s fd: %d", filetype_to_str(file->type), file->fd);
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
	int	total;
	int	seen;

	seen = 0;
    if (!root)
	{
		ft_debugf(77, "(empty)\n");
		return ;
	}
	total = child_count(root->first, root->second);
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
    if (root && root->first)  debug_tree_inner(root->first,  "", (++seen == total));
    if (root && root->second) debug_tree_inner(root->second, "", (++seen == total));
}
