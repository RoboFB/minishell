/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:47:34 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/17 15:22:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

/*

minishell not bash action chain

1. init
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

typedef enum e_operator
{
	// no child
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_ERROR,
	REDIRECTION_APPEND,
	REDIRECTION_HERE_DOC,

	// has childs
	CHILD_PIPE, // |
	CHILD_AND, // &&
	CHILD_OR, // ||
}	t_operator;

typedef struct s_command t_command;

typedef struct s_command
{
	t_operator		child_type;

	t_command		*parent; // NULL if root
	t_command		*child_left; // NULL if no child
	t_command		*child_right; // NULL if no child

	char			*name;
	char			**args;
	char			*file; // only for Redirection
	char			*limiter; // only for Here_doc

	// int				input_fd; // std:0
	// int				output_fd; // std:1
	// int				error_fd; //std:2

}	t_command;





// auto

#endif
