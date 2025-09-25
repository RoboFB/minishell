

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
- [x] ''
- [x] "" with $
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

- [ ] env _=/usr/bin/env  /minshell apsolut
- [ ] fix EXIT_FAILURE to correct exit number



## Functions

readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, Add_history,

malloc, free,
write, access, open, read,
close, 
fork, 
wait, waitpid, wait3, wait4,

signal, sigaction, sigemptyset, sigaddset, kill, 
exit,
getcwd,
chdir, stat, lstat, fstat, unlink,
execve,
dup, dup2, Pipe,
opendir, readdir, closedir,

strerror, perror, printf, 
isatty, ttyname, ttyslot, ioctl,
getenv, 
tcsetattr, tcgetattr,
tgetent, tgetflag, tgetnum, ttgetstr, tgoto, tputs
