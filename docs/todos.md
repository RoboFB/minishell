

## Random
- [ ] Makefile
- [x] Garbed collector?
- [ ] signals
- [ ] history
- [ ] one global variable for signal number

## Parts / main loop
- [ ] init
- [x] Prompt
- [x] Lexing
- [x] Parsing
- [x] expand symbols
- [ ] execution
- [ ] free

## parsing symbols
- [x] ''
- [x] "" with $
- [x] <
- [x] >
- [ ] <<
- [x] >>
- [x] |
- [x] $
- [x] $?
- [x] $$
- [ ] *

## parsing
- [x] collect heredocs before execution
- [x] expand when hitting each command
- [x] << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
- [ ] set shell level
- [x] accept redirect ahead of command
- [x] in cases like a""b, the current quote joiner turns the whole thing into a b, instead of ab. This is likely because I don't mark quotes as contained in a quote so after stripping there's no indicator of it having been in quotes.
- [ ] expansions on file redirects, check order and guard against multiple files. handle redirect expansions separately from arg expansions.
- [ ] attach redirect-only atoms to relevant expression.
- [x] export var="echo hi" && "$var" should error "echo hi: command not found"
- [ ] (mostly) ignore tokens and just read until next non alnum/_ char for variables. if no variable relevant (alnum/_) chars follow, $ should be treated as literal


## signals
- [ ] handle ctrl+c, ctrl+d && ctrl+\
- [ ] handle animation cues

## execution
- [x] single cmd.
- [x] < redirect input.
- [x] > redirect output.
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
- [x] refactor run with no command.
- [x] shell level.
- [] no interctiv mode for testers. + testing
- [] * working dir an matching globla.
- [] somehow i redirect error to stdout and not stderror like: rhhhrhrhr > /dev/null

- [x] check out: readline
- [ ] main loop, test stuff out

- [x] env _=/usr/bin/env  /minshell apsolut -> ignore it
- [x] fix EXIT_FAILURE to correct exit number

- [x] add $?
- [x] Fix env varable like la li lu   of export la li lu (no =)

BIG F BIG BIG F

(export V=v | (echo $V && export U=u && echo $U) | cat -e) && echo $V
              (        --sub shell--           )

for something like that:
(echo im hear, meno && sleep 5 && echo hi) | (ping -c 2 1.1.1.1 && cat -e)

do we keep executing in this case:
(export testing="Makefile .gitignore" && echo bob > WTF < $testing) 2> /dev/null  || echo 2
result:
/dev/null: bash: $testing: ambiguous redirect
stdout: 2

cat < Makefile > 1 | cat < Makefile > 1




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

*foo*
f*oo
f*oo*oo

src/**/*.c
