# linux-shell
project to explore and learn basics of linux by making a linux shell
🐚 MyShell – A Minimal Linux Shell in C++
Overview

MyShell is a minimal Linux shell implemented in C++ to understand how Unix shells work internally.
It supports command execution, built-in commands, input/output redirection, and multi-stage pipelines using low-level system calls like fork, execvp, pipe, and dup2.

This project focuses on process control and file descriptor management, not advanced parsing.

Features
 Supported

Interactive REPL loop

Execution of external commands (ls, echo, cat, etc.)

Built-in commands:

cd

exit

Input redirection: <

Output redirection: >

Output append redirection: >>

Single and multiple pipelines (|)

Combination of pipes and redirection
(e.g. cat < in.txt | sort | uniq -c > out.txt)

Proper process cleanup using waitpid

 Not Supported (by design)

Quoted strings (" " or ' ')

Escape sequences (\n, \t, etc.)

Environment variables ($PATH, $HOME)

Globbing (*, ?)

Background execution (&)

stderr redirection (2>, &>)

These features require a full shell parser and are intentionally omitted.

How It Works (High Level)

Read user input in a loop (REPL)

Tokenize input by whitespace

Handle built-in commands

Parse redirection operators (<, >, >>)

Split commands by pipe (|)

Create pipelines using pipe()

Fork child processes

Set up stdin/stdout using dup2

Execute commands using execvp

Parent waits for all child processes

Compilation
g++ main.cpp -o myshell

Running the Shell
./myshell

Example Commands
Basic command
ls

Input redirection
cat < file.txt

Output redirection
ls > out.txt

Append output
echo hello >> log.txt

Pipeline
ls | wc -l

Pipeline + redirection
cat < data.txt | sort | uniq -c > result.txt

Sample Test Case
echo alpha > in.txt
echo beta >> in.txt
echo alpha >> in.txt

cat < in.txt | sort | uniq -c


Expected output:

      2 alpha
      1 beta

Learning Outcomes

Understanding Unix process creation (fork)

Replacing process images (execvp)

File descriptor manipulation

Pipe-based inter-process communication

Correct resource cleanup

Shell execution flow

Future Extensions

Quote and escape parsing

Environment variable expansion

Job control (&, fg, bg)

stderr redirection

Command history

Tab completion

Author

Built as a learning project to understand Linux internals and shell execution.
