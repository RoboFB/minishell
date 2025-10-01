/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:47:34 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/30 13:26:28 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

/*

minishell not bash action chain

1. init (setup):
- redirects
- pipes and && and ||
- here_docs

2. forken

3. open/set the files/fds

4. execute

- buildin?
- find in path
- any / -> direct execution



child 1 use one end of pipe and close the other end
child 2 use the other end of pipe and close the other end
parent close both ends of pipe

REDIRECTION_INPUT     <   rm: fd:0(stdin)    new: (create file) in read
REDIRECTION_OUTPUT    >   rm: fd:1(stdout)   new: (open file) in write
REDIRECTION_ERROR     >   rm: fd:2(stderr)   new: (open file) in write
REDIRECTION_APPEND   >>   rm: fd:1(stdout)   new: (open file) in append
RE..N_INPUT_HERE_DOC <<   rm: fd:0(stdin)    new: (create file) in read

*/

/* 
exit codes between 0-255
above 125 special meaning

SUCCESS -> 0

Failures: any !=0
on signal -> 128 + signal num
command not found in child -> 127
command found but not executable in child -> 126
expansion error, redirection error -> grater than 0

builtin errors:
SUCCESS -> 0
FAILURE -> any !=0
incorrect usage?  called incorrectly -> 2  expl. wrong flag, unknown options, wrong number of arguments syntax error
*/



typedef enum e_exit_code
{
	// bash + builtins
	EXIT_OK = EXIT_SUCCESS,// == EXIT_SUCCESS
	EXIT_GENERAL_ERROR = EXIT_FAILURE, // == EXIT_FAILURE
	EXIT_SYNTAX_ERROR = 2, // + wrong usage of builtins
	
	// builtins
	EXIT_BLT_CMD_NOT_EXECUTABLE = 126,
	EXIT_BLT_CMD_NOT_FOUND = 127,
	
	// general
	EXIT_SIGNAL_BASE = 128, // + signal number
	EXIT_MAX = 255,

}	t_exit_code;


// auto

#endif
