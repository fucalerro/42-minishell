# 42-minishell
```C
while(1)
{
  get_prompt();
  parse_prompt();
  if (fork != NULL)
      wait( NULL);
  else
      execve();
}
```
## allowed external function
| Function Name | Library | Description |
|---------------|---------|-------------|
| `readline` | `<readline/readline.h>` | Reads a line from the terminal with editing features. |
| `rl_clear_history` | `<readline/history.h>` | Clears the readline history list. |
| `rl_on_new_line` | `<readline/readline.h>` | Informs readline of a new line. |
| `rl_replace_line` | `<readline/readline.h>` | Replaces the current line in the readline buffer. |
| `rl_redisplay` | `<readline/readline.h>` | Updates the readline display. |
| `add_history` | `<readline/history.h>` | Adds a new item to the readline history. |
| `printf` | `<stdio.h>` | Outputs formatted data to standard output. |
| `malloc` | `<stdlib.h>` | Allocates specified memory size. |
| `free` | `<stdlib.h>` | Frees allocated memory. |
| `write` | `<unistd.h>` | Writes data to a file descriptor. |
| `access` | `<unistd.h>` | Checks file accessibility. |
| `open` | `<fcntl.h>` | Opens a file or device. |
| `read` | `<unistd.h>` | Reads data from a file descriptor. |
| `close` | `<unistd.h>` | Closes a file descriptor. |
| `fork` | `<unistd.h>` | Creates a new process. |
| `wait` | `<sys/wait.h>` | Waits for a child process to end. |
| `waitpid` | `<sys/wait.h>` | Waits for a specific child process. |
| `wait3`, `wait4` | `<sys/wait.h>` | Variants of wait with more options. |
| `signal` | `<signal.h>` | Sets a signal handler. |
| `sigaction` | `<signal.h>` | Changes a signal action. |
| `sigemptyset` | `<signal.h>` | Initializes an empty signal set. |
| `sigaddset` | `<signal.h>` | Adds a signal to a set. |
| `kill` | `<signal.h>` | Sends a signal to a process. |
| `exit` | `<stdlib.h>` | Exits the process. |
| `getcwd` | `<unistd.h>` | Gets the current working directory. |
| `chdir` | `<unistd.h>` | Changes the working directory. |
| `stat`, `lstat`, `fstat` | `<sys/stat.h>` | Gets file information. |
| `unlink` | `<unistd.h>` | Deletes a file. |
| `execve` | `<unistd.h>` | Executes a program. |
| `dup`, `dup2` | `<unistd.h>` | Duplicates a file descriptor. |
| `pipe` | `<unistd.h>` | Creates a pipe. |
| `opendir` | `<dirent.h>` | Opens a directory stream. |
| `readdir` | `<dirent.h>` | Reads a directory entry. |
| `closedir` | `<dirent.h>` | Closes a directory stream. |
| `strerror` | `<string.h>` | Describes an error number. |
| `perror` | `<stdio.h>` | Prints an error message. |
| `isatty` | `<unistd.h>` | Tests if a file descriptor is a terminal. |
| `ttyname` | `<unistd.h>` | Returns the terminal name. |
| `ttyslot` | `<unistd.h>` | Finds the utmp slot. |
| `ioctl` | `<sys/ioctl.h>` | Controls special file parameters. |
| `getenv` | `<stdlib.h>` | Retrieves an environment value. |
| `tcsetattr`, `tcgetattr` | `<termios.h>` | Sets/gets terminal attributes. |
| `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs` | `<term.h>` | Functions for terminal control via the terminfo database. |

# Minishell Development To-Do List

## Basic Shell Features
- [x] Display a prompt when waiting for a new command.
- [ ] Implement a working history feature.

## Command Execution
- [x] Search and launch the correct executable based on the PATH variable or using a relative/absolute path.

## Signal Handling
- [ ] Use only one global variable to indicate a received signal.
- [ ] Ensure the global variable only stores the number of the received signal.
- [ ] Do not use "norm" type structures in the global scope for signal handling.

## Input Parsing and Interpretation
- [ ] Do not interpret unclosed quotes or special characters (e.g., `\`, `;`).
- [ ] Handle single quotes (`'`): ignore metacharacters within the quotes.
- [ ] Handle double quotes (`"`): ignore metacharacters except for `$` within the quotes.

## Redirections
- [x] Implement input redirection using `<`.
- [ ] Implement output redirection using `>`.
- [ ] Implement here-document (`<<`) with a delimiter (do not update history).
- [ ] Implement output append redirection using `>>`.

## Pipes
- [x] Implement pipe functionality (`|` character).

## Environment Variables and Exit Status
- [ ] Handle environment variables expansion (`$` followed by characters).
- [ ] Handle `?` which expands to the exit status of the last executed foreground pipeline.

## Special Key Handling (Interactive Mode)
- [ ] Handle `ctrl-C`: display a new prompt on a new line.
- [ ] Handle `ctrl-D`: exit the shell.
- [ ] Handle `ctrl-\`: no action.

## Built-in Commands
- [ ] Implement `echo` with `-n` option.
- [x] Implement `cd` with only a relative or absolute path.
- [x] Implement `pwd` with no options.
- [ ] Implement `export` with no options.
- [ ] Implement `unset` with no options.
- [ ] Implement `env` with no options or arguments.
- [ ] Implement `exit` with no options.

