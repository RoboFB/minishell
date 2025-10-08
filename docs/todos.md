

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
- [x] single cmd.
- [x] < redirect input.
- [x] > redirect output.
- [ ] << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
- [x] >> should redirect output in append mode
- [x] | pipes


## built-ins
- [x] echo		with option -n
- [x] cd		with only a relative or absolute path
- [x] pwd		with no options
- [x] export	with no options
- [x] unset		with no options
- [x] env		with no options or arguments
- [x] exit		with no options




## Robin random
- [x] check out: readline
- [ ] main loop, test stuff out

- [ ] env _=/usr/bin/env  /minshell apsolut
- [ ] fix EXIT_FAILURE to correct exit number

- [ ] add $?


BIG F BIG BIG F

(export V=v | (echo $V && export U=u && echo $U) | cat -e) && echo $V
             (        --sub shell--           )

for something like that:
(echo im hear, meno && sleep 5 && echo hi) | (ping -c 2 1.1.1.1 && cat -e)


#### readline
read on line gets mallocte new line

#### rl_redisplay
Change what's displayed on the screen to reflect the current contents of rl_line_buffer.

#### rl_on_new_line
Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.

#### rl_replace_line,
what it says
#### add_history, 
what it says
#### rl_clear_history, 
what it says



## Functions

readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, Add_history,

malloc, free,
write, access, open, read,
close, 
fork, 
wait, waitpid, wait3, wait4,

signal, // lagace don't use it
sigaction, sigemptyset, sigaddset, kill, 
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
