*This project has been created as part of the 42 curriculum by cprot, scavalli.*

# minishell

> As beautiful as a shell — a recreation of bash in C.

## Description

minishell is a UNIX shell written in C. The goal is to understand how shells work internally: lexing, parsing, executing commands, managing processes, handling signals, and dealing with file descriptors. The reference behavior is bash.

Features implemented:
- Interactive prompt with command history
- Executable search via `PATH` or relative/absolute paths
- Single and double quote handling
- Redirections: `<`, `>`, `<<`, `>>`
- Pipes (`|`) — chaining commands
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling: `ctrl-C`, `ctrl-D`, `ctrl-\`
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

## Instructions

```bash
# Clone and build
git clone [your_repo] && cd [your_repo]
make

# Run
./minishell
```

No arguments required. The shell launches in interactive mode.

## Usage examples

```bash
minishell$ ls -la | grep ".c" | wc -l
minishell$ export MY_VAR=hello && echo $MY_VAR
minishell$ cat << EOF
minishell$ echo "exit status: $?"
```

## Resources

- [Bash manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Writing a shell in C — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [POSIX fork/exec/wait](https://man7.org/linux/man-pages/man2/fork.2.html)
- [GNU readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)
- **AI usage:** Claude was used to clarify edge cases in quote parsing and signal behavior. All parsing logic and execution were written and tested manually.
