/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:59:30 by modiepge          #+#    #+#             */
/*   Updated: 2025/11/06 15:16:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "public_struct.h"

/*	2.	functions
		2.1	heredoc
*/
void					heredoc_collect(t_token *token, char *tmpfile);
void					heredoc_set(t_token *token, int pid, char *tmpfile);
void					heredoc_in(t_token **token);
t_token					*get_delimiter(t_token *token, t_tokens *list);
void					set_delimiters(t_tokens *list);
int						heredoc_open(const char *path, int flags,
							int permissions);
char					*tmpfile_name(unsigned int id);
ssize_t					write_until_variable(int fd, char *bytes);
ssize_t					write_variable(int fd, char *bytes,
							t_token_type quoted);
int						heredoc_expand(int fd, char *bytes,
							t_token_type quoted);
t_file					*heredoc_write(t_file *file);

/*		2.2	parsing and processing
*/
void					parse(char *line, t_tokens *list);
void					strip_quotes(t_tokens *tokens);
void					strip_leftover_vars(t_tokens *tokens);
void					strip_whitespace(t_tokens *tokens);
void					join_quotes(t_tokens *list);
void					quote(t_tokens *list);
void					expression_add_arg(t_expression *atom,
							t_token *token);
void					process(t_tokens *list);
void					set_path(t_file *file);
void					resolve_files(t_expression *expression);
void					resolve(t_expression *expression);
t_token					*list_skip_whitespace(t_token *token);
void					list_reset(t_tokens *tokens);
bool					list_trim(t_tokens *list);
t_token					*list_splice(t_token *token, t_tokens *list,
							t_tokens *new);
int						is_meta_chararacter(char c);
void					line_split(char *line, t_tokens *list);
const t_token_key		*tok_identify_meta_token(char *position);
int						tok_make_meta_token(char *position, t_tokens *list);
int						tok_make_word_token(char *position, t_tokens *list);
int						tok_make_space_token(char *position, t_tokens *list);
int						tok_variable(char *position, t_tokens *list);
int						tok_home(char *position, t_tokens *list);
int						token_is_space(t_token *token);
int						token_is_redirect(t_token *token);
int						token_is_operator(t_token *token);
int						token_is_parenthesis(t_token *token);
int						token_is_separator(t_token *token);
t_token					*tok_new(char *content, t_token_type type);
void					tok_add(t_token *new, t_tokens *list);
void					tok_delete(t_token **token, t_tokens *list);
void					tok_join(t_token *first, t_token *second,
							t_tokens *list);
t_filetype				token_to_filetype(t_token *token);
void					contract_file(t_token *atom, t_token **token);
t_token					*atomize(t_token **token);
void					contract(t_tokens *list);
void					tokenize(char *line, t_tokens *list);

/*		2.3	AST
*/
t_token					*token_next(t_token **token);
t_token					*token_peek(t_token **token);
t_expression			*nud(t_token **token);
t_expression			*led(t_token **token, t_expression *first,
							t_token *operator);
t_expression			*parse_expression(t_token **token,
							const int minimum_binding);
t_expression			*make_expression(t_expression_operator operator,
							t_expression *first, t_expression *second);
void					list_to_tree(void);
t_expression			*token_to_expression(t_token *token);
t_expression_operator	expression_type(t_token_type type);
t_bind					*binding_power(t_token *token);

/*		2.4	validation
*/
bool					valid_collection(t_tokens *list);
bool					valid_parenthesis(t_tokens *list);
bool					valid_order(t_tokens *list);
bool					valid_prompt(t_tokens *list);
bool					*interrupted(void);
int						syntax_error(char *message, char *near);

/*		2.5	variables
*/
void					tok_expansion(t_token *token, char *line,
							t_tokens *tokens);
bool					expand_logic(t_token *token, t_tokens *tokens);
void					expand(t_tokens *tokens);
void					receive_pid(int sig, siginfo_t *info, void *context);
pid_t					get_pid(void);
char					*get_home(t_token *token);

/*		2.6	wildcards
*/
void					replace_wildcards(t_tokens *list);
void					reset_wildcards(char *pattern);
bool					wild_check_name(char *name, char *pattern_pos);
bool					wild_is_last_ok(bool *last_wildcard, char *name,
							char *last_pattern);
bool					wild_found_next_match(bool wildcard, char **name,
							char *pattern);
void					wildcards(t_tokens *list);
void					wildcard_set(char *replace_str, t_tokens *list);
void					wild_add_steps(char *curent_path, char **pattern_pp,
							t_tokens *list);

#endif