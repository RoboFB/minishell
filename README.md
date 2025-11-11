



[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](#)
[![Bash](https://img.shields.io/badge/Bash-4EAA25?logo=gnubash&logoColor=fff)](#)
[![Git](https://img.shields.io/badge/Git-F05032?logo=git&logoColor=fff)](#)
![GitHub Repo stars](https://img.shields.io/github/stars/RoboFB/minishell)
![GitHub contributors](https://img.shields.io/github/contributors/robofb/minishell)
![GitHub labels](https://img.shields.io/github/labels/robofb/minishell)
![GitHub status](https://img.shields.io/github/checks-status/robofb/minishell/main)
![GitHub last-commit](https://img.shields.io/github/last-commit/robofb/minishell)
![GitHub repo size](https://img.shields.io/github/repo-size/robofb/minishell)
![GitHub license](https://img.shields.io/github/license/robofb/minishell)


## minishell - Bash copy in C

---
## Picture
---








## How to Install


``` bash
git clone https://github.com/RoboFB/minishell.git
cd minishell
make
./minishell
```



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

## Files structure
```
minishell
├── include
├── libft
│   ├── include
│   ├── obj
│   └── src
├── Makefile
├── minishell
├── obj
├── README.md
└── src
	├── main.c
	├── animation
	├── execution
	├── parsing
	└── utils
		└── garbage_collector
```






## About The Project


### Built With


### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```


### Installation/Run


1. Get a free API Key at [https://example.com](https://example.com)
2. Clone the repo
   ```sh
   git clone https://github.com/github_username/repo_name.git
   ```
3. Install NPM packages
   ```sh
   npm install
   ```
4. Enter your API in `config.js`
   ```js
   const API_KEY = 'ENTER YOUR API';
   ```
5. Change git remote url to avoid accidental pushes to base project
   ```sh
   git remote set-url origin github_username/repo_name
   git remote -v # confirm the changes
   ```





<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="## minishell - Bash copy in C">back to top</a>)</p>



## Allowed Functions

* malloc, free,
* write, open, read, close,
* dup, dup2, Pipe,
* opendir, readdir, closedir,
* fork, execve, wait, waitpid, wait3, wait4,
* exit, strerror, perror, printf,
* getenv, getcwd, chdir, access,
* readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, Add_history,
* signal, sigaction, sigemptyset, sigaddset, kill,
* stat, lstat, fstat, unlink,
* isatty, ttyname, ttyslot, ioctl,
* tcsetattr, tcgetattr,
* tgetent, tgetflag, tgetnum, ttgetstr, tgoto, tputs

### Top contributors:

<a href="https://github.com/robofb/minishell/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=robofb/minishell" alt="contrib.rocks image" />
</a>




## License

Distributed under the Unlicense License. See `LICENSE.txt` for more information.




## Acknowledgments

* [GNU Bash manual](https://www.gnu.org/software/bash/manual/bash.html)
* [ Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)
* [Pret Paring core dump video](https://youtu.be/0c8b7YfsBKs?si=AitdZJebN1rQwKYC)
* [42 Heilbronn](https://www.42heilbronn.de/de/)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->


