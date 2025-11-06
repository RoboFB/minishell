/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:59:40 by rgohrig           #+#    #+#             */
/*   Updated: 2025/11/06 15:18:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #define _POSIX_C_SOURCE 202405L
// #define _DEFAULT_SOURCE

# include <stdlib.h>	// malloc, free, getenv, exit
# include <unistd.h>	// read, write, close, access, fork, execve, 
//				pipe, dup, dup2, chdir, getcwd, isatty, unlink, ttyslot, ttyname
# include <fcntl.h>		// open, (O_* flags)
# include <dirent.h>	// opendir, readdir, closedir

// # include <sys/types.h>	// pid_t and other system types
# include <sys/wait.h>	// wait, waitpid, wait3, wait4
// # include <sys/time.h>	// timeval (used by wait3/wait4)
// # include <sys/resource.h> // rusage (used by wait3/wait4)
# include <errno.h>		// (errno)
# include <string.h>	// strerror
// # include <sys/stat.h>	// stat, lstat, fstat
// # include <termios.h>	// tcsetattr, tcgetattr
// # include <term.h>		// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <stdio.h>		// printf, perror
# include <readline/readline.h>	// readline, rl_clear_history,
// 								rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>	// add_history
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill
// # include <sys/ioctl.h>	// ioctl
# include <stdbool.h>	// bool type (is not a function)
# include <limits.h>	// INT_MAX, PATH_MAX (is not a function)

// libft
# include "libft.h"
# include "libft_gnl.h"
# include "libft_printf.h"
# include "libft_styles.h"

// structs
# include "public_struct.h"

// other stuff
# include "execution.h"
# include "parsing.h"
# include "utils.h"
# include "animation.h"

#endif
