

## Random
- [ ] Makefile
- [ ] Garbed collector?
- [ ] signals
- [ ] history
- [ ] one global variable for signal number


## Parts / main loop

- [ ] init
- [ ] Prompt
- [ ] Lexing
- [ ] Parsing
- [ ] expend symbols
- [ ] execution
- [ ] free


## parsing symbols
- [ ] ''
- [ ] "" with $
- [ ] <
- [ ] >
- [ ] <<
- [ ] >>
- [ ] |
- [ ] $
- [ ] $?



## execution
- [ ] single cmd.
- [ ] < redirect input.
- [ ] > redirect output.
- [ ] << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
- [ ] >> should redirect output in append mode
- [ ] | pipes


## built-ins
- [ ] echo		with option -n
- [ ] cd		with only a relative or absolute path
- [ ] pwd		with no options
- [ ] export	with no options
- [ ] unset		with no options
- [ ] env		with no options or arguments
- [ ] exit		with no options




## Robin random
- [ ] check out: readline
- [ ] main loop, test stuff out





## Functions

Readline, Rl_clear_history, Rl_on_new_line,
Rl_replace_line, Rl_redisplay, Add_history,

Malloc, Free,
Write, Access, Open, Read,
Close, 
Fork, 
Wait, Waitpid, Wait3, Wait4,

Signal, Sigaction, Sigemptyset, Sigaddset, Kill, 
Exit,
Getcwd,
Chdir, Stat, Lstat, Fstat, Unlink,
Execve,
Dup, Dup2, Pipe,
Opendir, Readdir, Closedir,

Strerror, Perror, Printf, 
Isatty, Ttyname, Ttyslot, Ioctl,
Getenv, 
Tcsetattr, Tcgetattr,
Tgetent, Tgetflag, Tgetnum, Ttgetstr, Tgoto, Tputs
