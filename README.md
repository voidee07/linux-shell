# linux-shell
project to explore and learn basics of linux by making a linux shell
Unix Shell from Scratch (C/C++)

A minimal Unix-like shell implemented in C/C++ to understand Linux system internals such as process creation, execution, and inter-process communication.

Features

Execute external commands using fork() and exec

Input and output redirection (<, >)

Command piping using |

File descriptor manipulation with dup2()

Process synchronization using wait()

Tech Stack

Language: C / C++

Platform: Linux

Core Concepts: System calls, file descriptors, pipes, IPC

How It Works

The shell parses user input, creates child processes using fork(), sets up pipes and redirections via dup2(), executes commands using exec, and waits for process completion using wait().

Build & Run
g++ shell.cpp -o shell
./shell

Example Usage
ls | wc -l
cat < input.txt > output.txt

Limitations

No built-in commands (cd, exit)

No background execution or job control

Not fully POSIX-compliant

Purpose

Built for educational purposes to gain hands-on experience with Unix process management and low-level system programming.
