_This project has been created as part of the 42 curriculum by chguerre, rpinheir_

[![C/C++ CI](https://github.com/SailMasterG/minishell/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/SailMasterG/minishell/actions/workssflows/c-cpp.yml)

# Description

**Minishell** is a 42 team project where it's main goal is to build a simplified shell.
In this project, the goal is to have a working shell with the same behaviour as **bash**, or at least what is possible to do.

# Main functional parts of Minishell project:

# 1. Parsing:

The parsing must get the input from the user and categorize each word into a categorize it.
Per example a pipe '|' is of category PIPE, a command like `cat Readme.md` are splitted then into two words (by whitespaces)
and categorized 'cat' is a WORD and README.md is also a WORD.
After each word in the input is categorized, we will then build what is called an AST, where everything is linked, the first node of commands have all the arguments
and all the redirections that have been built by the parser.
Per example ``` cat << EOF | grep $USER > user.txt:

# 2. Execution

Its in this part where we are going to setup the pipes, open files and **execute** the commands from the AST that was built by the parsing,
see how many commands, open each file (fd) and setup the initialisation to have a working redirection and piping to execute properly the command given as input.
Within the scope, we manage pipes, redirections, Posix signals like SIGINT (CTRL+C), build history based on recent inputs.
There is also a environment cloning where we must manage environment variables, and so also using '$?' to get the exit status of the most recent execution and be able
tokens expand variables with character '$'.

# 3. Built-ins

This part is where we build commands such as `echo` or even `export`, instead of using system programs we program our own following the same behaviour as bash
built-ins.

# Instructions

To build the project:

```bash
make
```

To run it you can either:

```bash
make run
```

or

```bash
./minishell
```

### This will launch the program and will run until you close it (Ctr+D, exit, etc...)

Feel free to test with those examples:

```bash
ls -la
```

```bash
cat << A << B
```

```bash
ls | grep .c | wc -l
```

```bash
cat README.md | grep "Instructions"
```

```bash
cat << eof > here.log | cat here.log | grep "$USER"
USER
$USER
eof
```

# Resources

### AI usage

AI has been used for debugging purposes only, it has also been used to introduce new notions aside from reading other sources to get a better understanding quicker.
Other than that, no AI has been used to do the coding in our place.

### Minishell 42 Guides

## Parsing/Lexer Theory

- [Intro to Parsing & Lexing](https://dev.to/elipie/intro-to-parsing-lexing-3g01) -- basics for beginners
- [Shell parsing tips](https://shell.multun.net/parser.html) -- shell parser in detail
- [Bash guide on expansion/substituition](https://thealternative.ch/en/bash)

## Videos

- [Bash Shell Operation In Depth](https://youtube.com/watch?v=GGNzB_o4OiM) -- how bash processes a command
- [Build a simple shell in C](https://youtube.com/watch?v=yTR00r8vBH8) -- shell from scratch

## Others:

- [Code crafters](https://app.codecrafters.io/courses/shell/overview) -- non 42 project that is also very close to what we have to do
