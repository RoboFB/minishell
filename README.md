<div align="center">

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![Bash](https://img.shields.io/badge/Bash-4EAA25?logo=gnubash&logoColor=fff)](#)
[![Git](https://img.shields.io/badge/Git-F05032?logo=git&logoColor=fff)](#)
![GitHub last commit](https://img.shields.io/github/last-commit/RoboFB/minishell/main)
![GitHub Repo stars](https://img.shields.io/github/stars/RoboFB/minishell)
<!-- ![GitHub license](https://img.shields.io/github/license/robofb/minishell) -->

</div>

&nbsp;

<h1 align="center">
  🐚 minishell
</h1>

<h3 align="center">
  a small, expandable and animated shell to learn
</h3>

<div align="center">
<img src="docs/example.gif" alt="Example">
</div>

&nbsp;



## Wall of Text
It’s the first group project of the [42 Heilbronn](https://www.42heilbronn.de/de/) core curriculum.
The main goal is to recreate a small shell similar to Bash. While relying only on a handful of C functions and system calls. 
With two big parts parsing(Moritz) and execution(Robin). The difficult part was to structuring the code, and complying with the 42 Norm — for example 25 line limit for functions.
During the deep dive, we discovered many edge cases and custom Bash behaviors, such as ambiguous redirects.
Overall, it was a great learning experience. Big thanks to my partner, Moritz Diepgen.



## Key features
- Command parsing and tokenization
- Execution via fork/execve
- Builtins: cd, echo, pwd, export, unset, env, exit
- Pipes, redirections and heredoc (`|`, `>`, `>>`, `<`, `<<`)
- Logic operators (`||`, `&&`)
- Basic signal handling for interactive mode
- Optional small prompt animation (`-a`)



## Allowed functions (summary)
The project was completed under a constrained set of allowed functions. Commonly used calls include:

- malloc, free
- write, open, read, close, perror
- dup, dup2, pipe
- fork, execve, wait, waitpid
- opendir/readdir/closedir
- readline
- signal/sigaction



## Feedback
some feedback we received in the evaluation of the project:
- 100 minutes of pure agony and tears. this was quite eval. those guys absolutely rock. 
- I can definitely say that they KNOW what they did.
- Hands down the most impressive minishell I've seen so far.
- They explained clearly the logic and the implementation of each part.



## Requirements
- Linux (POSIX-compatible)
- gcc or clang
- make



## Quick start — build & run
### Clone and Built
```bash
git clone https://github.com/RoboFB/minishell.git
cd minishell
make
```
If the compiling fails check `CC` and `CFLAGS` in both `Makefile`. Try to use `CC=gcc` or `CC=clang`.

### Run
```bash
./minishell        # add --animation or -a to enable animations
```



## Project layout (short)
```
minishell/
├── include/     # headers
├── libft/       # own library
├── obj/         # binary files (builded)
└── src          # implementation
│   ├── animation/
│   ├── execution/
│   ├── parsing/
│   ├── utils/
│   └── main.c
├── Makefile
├── minishell    # executable (builded)
└── README.md  
```



## Acknowledgments
- [42 Heilbronn](https://www.42heilbronn.de/de/)
- [GNU Bash manual](https://www.gnu.org/software/bash/manual/bash.html)
- [ Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
- [Pret Paring core dump video](https://youtu.be/0c8b7YfsBKs?si=AitdZJebN1rQwKYC)
