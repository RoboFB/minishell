<div align="center">

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![Bash](https://img.shields.io/badge/Bash-4EAA25?logo=gnubash&logoColor=fff)](#)
[![Git](https://img.shields.io/badge/Git-F05032?logo=git&logoColor=fff)](#)
![GitHub last commit](https://img.shields.io/github/last-commit/RoboFB/minishell/main)
<!-- ![GitHub Repo stars](https://img.shields.io/github/stars/RoboFB/minishell) -->
<!-- ![GitHub license](https://img.shields.io/github/license/robofb/minishell) -->

</div>

&nbsp;



<h1 align="center"> 
  🐚 minishell
</h1>

<h3 align="center">
  a small, expandable and animated shell to learn
</h3>


### example line

export var=Hallo && echo $var && ls | grep invalid-name || cat -e << EOF




A minimal educational Unix shell written in C. Implemented as a school project (42 Heilbronn) to demonstrate command parsing, process control, redirections, pipes, builtins, and basic signal handling.

Why this project
-----------------
This repository implements a small, functional shell to learn how shells work: reading input, parsing commands, forking processes, handling IO redirection and pipelines, and implementing builtin commands.

Key features
------------
- Command parsing and tokenization
- Execution via fork/execve
- Builtins: cd, echo, pwd, export, unset, env, exit
- Pipes and redirections (>, >>, <, heredoc `<<`)
- Basic signal handling for interactive mode
- Optional small prompt animation

Requirements
------------
- Linux (POSIX-compatible)
- gcc or clang
- make

Quick start — build & run
-------------------------
Clone, build and run the project.

```bash
git clone https://github.com/RoboFB/minishell.git
cd minishell
make
./minishell        # add --animation oe -a to enable it
```

Testing
-------
This repo includes `minishell_tester/` that contains many test cases. See that folder for instructions — many tests expect bash-like behavior.

Project layout (short)
----------------------
```
minishell/
├── include/		#headers
├── libft/
├── obj/
└── src				# implementation
│   ├── animation/
│   ├── execution/
│   ├── parsing/
│   ├── utils/
│   └── main.c
├── Makefile
├── minishell		# executable after build
└── README.md


minishell/
├── include/         # public headers
├── libft/           # bundled libft implementation
├── obj/             # object files
├── src/             # implementation
│   ├── animation/
│   ├── execution/
│   ├── parsing/
│   └── utils/
├── minishell        # built executable (after make)
├── Makefile
└── README.md
```

Allowed functions (summary)
---------------------------
The project was completed under a constrained set of allowed functions. Commonly used calls include:

- malloc, free
- write, open, read, close
- dup, dup2, pipe
- fork, execve, wait, waitpid
- opendir/readdir/closedir
- readline and helpers
- signal/sigaction, tcgetattr/tcsetattr

See `include/` headers or project instructions for the definitive list.

Contributing
------------
This is mainly a student project, but small improvements are welcome. Please:

- Open an issue describing bugs or enhancements.
- Send focused pull requests and include tests when possible.

License
-------
Distributed under the Unlicense. See `LICENSE.txt` for details.

Acknowledgments
---------------
- GNU Bash manual
- POSIX Shell and Utilities specification
- 42 School project guidelines
