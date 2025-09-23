/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:47:34 by rgohrig           #+#    #+#             */
/*   Updated: 2025/09/22 17:26:12 by rgohrig          ###   ########.fr       */
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


// auto

#endif
