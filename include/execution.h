/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:47:34 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/06 14:25:24 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/* EXECUTION: STEPS

init:
garbage collector
environment
signals

loop:
clear gc temporary
passing
execute

exit:
cleanup all

execute:
backtrack the tree;
   setup files and fork for pipes

open/set the files/fds
execute the program
*/

/*
REDIRECTION_INPUT     <   rm: fd:0(stdin)    new: (create file) in read
REDIRECTION_OUTPUT    >   rm: fd:1(stdout)   new: (open file) in write
REDIRECTION_ERROR     >   rm: fd:2(stderr)   new: (open file) in write
REDIRECTION_APPEND   >>   rm: fd:1(stdout)   new: (open file) in append
RE..N_INPUT_HERE_DOC <<   rm: fd:0(stdin)    new: (create file) in read
*/

/* EXIT CODES:

exit codes are between 0-255 and above 125 they have a special meaning

General:
  0: SUCCESS
 !0: Failures
  1: general error
  2: syntax error, incorrect usage, called incorrectly
	 expl. wrong flag, unknown options, wrong number of arguments

Special:
  On signal:   128 + signal num
  command found but not executable in child -> 126
  command not found in child -> 127
  expansion error, redirection error -> grater than 0

builtin errors:
  0: SUCCESS
 !0: Failures

*/

// builtins

void		blt_unset(t_expression *cmd);
void		blt_echo(t_expression *cmd);
void		blt_noname(t_expression *command);
void		blt_cd(t_expression *cmd);
void		blt_exit(t_expression *cmd);
void		blt_export(t_expression *cmd);
int			blt_count_args(t_expression *cmd);
bool		blt_has_flag(t_expression *cmd);
void		blt_pwd(t_expression *cmd);
void		blt_env(t_expression *cmd);
void		blt_export_to_env_helper(t_expression *cmd, int *exit_code);
void		*h_get_builtin(t_expression *command);
void		run_builtin(t_expression *command);
bool		is_builtin(t_expression *command);

// error handling

void		msg_error(char *function, char *error);
void		set_exit_code(t_exit_code exit_code);
void		exit_shell(t_exit_code exit_code);
void		perror_exit(char *msg, t_exit_code exit_code);
void		perror_msg_exit(
				char *msg_start, char *msg_end, t_exit_code exit_code);
void		msg_exit(char *function, char *error, t_exit_code exit_code);
void		msg_set_exit_code(
				char *function, char *error, t_exit_code exit_code);

// environment

char		***env_get_ptr(void);
void		env_init(char **input_envp);
void		env_add_line(char *line);
void		env_add_line_data(char *key, char *value);
void		env_remove_line(char *line);
size_t		env_get_len_key(char *line);
int			env_get_size(char **environment);
char		**env_get_line_ptr(char *line);
char		*env_get_line_data(char *line);

// execution run tree and comands

pid_t		run_tree(t_expression *cmd);
pid_t		run_pipe(t_expression *cmd);
pid_t		run_and_or(t_expression *cmd);
pid_t		run_cmd_switch(t_expression *cmd);
void		wait_and_set_exit_code(pid_t pid);

char		*get_cmd_path(const char *cmd_name, char *search_path);
void		pipe_add_front(t_expression *cmd);
bool		is_piped_direct(t_expression *cmd);

// files

void		inherit_files(t_expression *cmd);
int			set_all_redirect(t_file *head);
int			set_fd(t_file *file, int change_fd);
int			read_file(t_file *file, int change_fd);
int			write_file(t_file *file, int change_fd);
int			write_append_file(t_file *file, int change_fd);

// signals

void		ctrl_c(int sig);
void		sig_reset(void);
void		sig_init(void);

#endif
