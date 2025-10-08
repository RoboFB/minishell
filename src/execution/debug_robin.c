/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_robin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 21:17:24 by modiepge          #+#    #+#             */
/*   Updated: 2025/10/08 17:17:10 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        "PATH_STDIN_READ", "PATH_STDOUT_WRITE", "PATH_STDERR_WRITE", "PATH_STDOUT_WRITE_APPEND",
        "PATH_STDERR_WRITE_APPEND", "FD_HEREDOC_READ", "FD_PIPE_READ", "FD_PIPE_WRITE"
    };
    // static const char *typestring[8] = {
    //     "< stdin", "> stdout", "2> stderr", ">> stdout",
    //     "2>> stderr", "<< heredoc", "< pipe", "> pipe"
    // };
	if (type == NOT_SET)
		return ("NOT_SET");
    if (type >= 0 && type <= 7)
		return (typestring[type]);
    return ("UNKNOWN FILETYPE");
}

static void debug_args_aligned(const char *prefix)
{
    ft_fprintf(2, "%s", prefix);
    ft_fprintf(2, "  args:  ");
}

static void debug_files_aligned(const char *prefix)
{
    ft_fprintf(2, "%s", prefix);
    ft_fprintf(2, "  files: ");
}

static void debug_args(char **args)
{
	int index;

	index = 0;
    if (!args || !args[0])
	{
		ft_fprintf(2, "\n");
		return;
	}
    while (args[index]) {
        ft_fprintf(2, "%s%s", args[index], args[index + 1] ? " " : "");
		index++;
    }
    ft_fprintf(2, "\n");
}

static void debug_files_robin(t_file *file)
{
	if (!file)
	{
		ft_fprintf(2, "no file\n");
		return;
	}
	int count = 0;
	for (t_file *tmp = file; tmp; tmp = tmp->next)
		count++;
	ft_fprintf(2, "count=%d: ", count);
	while (file) {
		ft_fprintf(2, "typ=%s ", filetype_to_str(file->type));
		ft_fprintf(2, "fd=%d ", file->fd);
		if (file->path)
			ft_fprintf(2, "path=%s ", file->path);
		if (file->next)
			ft_fprintf(2, " \n                  ");
		file = file->next;
	}
	ft_fprintf(2, "\n");
}

static void debug_node(const t_expression *node)
{
    if (!node)
		return;
    ft_fprintf(2, "%s", operator_to_str(node->type));
    if (node->type == OPERATOR_CMD && node->name)
        ft_fprintf(2, " name \"%s\"", node->name);
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
    ft_fprintf(2, "%s%s", prefix, last ? "└─ " : "├─ ");
    debug_node(node);
    ft_fprintf(2, "\n");
    make_under_prefix(next_prefix, sizeof next_prefix, prefix, last);
    if (node->type == OPERATOR_CMD) {
        debug_args_aligned(next_prefix);
        debug_args(node->args);
        debug_files_aligned(next_prefix);
        debug_files_robin(node->files);
        return;
    }
    if (node->first)  debug_tree_inner(node->first,  next_prefix, (++seen == total));
    if (node->second) debug_tree_inner(node->second, next_prefix, (++seen == total));
}

#include <sys/file.h> // debuging only

void debug_tree_robin(t_expression *root)
{
	int			seen;
	
	flock(2, LOCK_EX); // debug is ilegal in production code

	seen = 0;
    if (!root)
	{
		ft_fprintf(2, "(empty)\n");
		return;
	}
    debug_node(root);
    ft_fprintf(2, "\n");
    if (root->type == OPERATOR_CMD) {
		ft_fprintf(2, "   ");
        debug_args_aligned("");
        debug_args(root->args);
        ft_fprintf(2, "   ");
        debug_files_aligned("");
        debug_files_robin(root->files);
		ft_fprintf(2, "\n");
        return;
    }
	const int	total = child_count(root->first, root->second);
    if (root->first)  debug_tree_inner(root->first,  "", (++seen == total));
    if (root->second) debug_tree_inner(root->second, "", (++seen == total));
	ft_fprintf(2, "\n\n");
	flock(2, LOCK_UN);// debug is ilegal in production code
}
