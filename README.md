# Minimal Unix Shell

This project is a minimal Unix-like shell written in C as the final project for CS50x. The shell, named `mysh`, was developed to deepen my understanding of system-level programming, process control, signals, job management, and how real-world shells like `bash` or `zsh` work behind the scenes.

Unlike full-featured shells, `mysh` focuses on implementing a core subset of shell functionality in a clean, readable, and testable way. It supports:

- Built-in commands such as `cd`, `pwd`, and `exit`
- Execution of external programs with command-line arguments
- Job control with support for `jobs`, `fg`, and `bg`
- Foreground and background process management using process groups and signals
- Signal handling (e.g., `SIGINT`, `SIGTSTP`) for interactive control
- Line editing and input history using the GNU `readline` library
- Error handling and a clean prompt loop

#### Video Demo:  [YOUTUBE](https://youtu.be/KZ55P2Vclgw)

## Features and Behavior

When started, the shell displays a simple prompt and waits for user input. Users can enter either built-in commands (e.g., cd ..) or launch external programs like ls, echo, gcc, etc.

The shell tracks background jobs using the jobs command, and users can bring jobs to the foreground or send them to the background using fg and bg. Job IDs and process groups are maintained internally, allowing for reasonably realistic job management. Signals like Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP) are forwarded to the correct processes.

For input, the shell uses readline, which enables command history, arrow key navigation, and line editing — essential features for a usable interactive shell.

## Design Decisions

Several design choices were made intentionally:

Use of readline: Instead of manually handling terminal input, readline provides robust line editing and history features with minimal code.

Manual job control: Instead of relying on system defaults, job tracking was implemented using waitpid, process groups, and terminal control (tcsetpgrp), to better understand Unix process hierarchies.

No background & support (yet): Although the shell handles background jobs via bg/fg, the syntax command & is not currently supported, due to parsing and process handling constraints.

Clear separation of modules: Input handling, parsing, and shell logic are separated to improve readability and maintainability.



## Motivation

This project facilitates a deeper understanding of Unix system calls, process management, and the interaction between a shell and the operating system at a low level. It serves as an effective practical exercise for exploring user-to-OS communication mechanisms.

## Project Structure

- **src/** — Contains all the source code files. Each module or component is separated into its own file or subdirectory to improve readability and manageability.

  - `main.c`: Contains the `main` function, which initializes the shell and enters the main loop.
  - `shell.c`: Implements the core shell loop — reading user input, parsing commands, executing built-ins, and launching external processes.
  - `input.c`: Manages user input with readline and handles shell prompt and terminal I/O.
  - `parser.c`: Responsible for splitting input lines into tokens, handling quoting and escaping, and building command structures.

- `Makefile`: Defines build rules for compiling the project with `gcc`, linking necessary libraries (like `readline`), and cleaning up.

- **include/** — Header files (if applicable) are stored here, defining interfaces and shared declarations used throughout the project.

- `README.md`: Project documentation (you’re reading it!)


## Build & Run

1. The program is compiled into an executable called mysh using the command:
    ```bash
    make
   
2. Once compiled, the shell can be launched from the terminal using:
    ```bash
    ./mysh

3. Use it like a normal shell. For example:
    ```bash
    ls
    cd ..
    exit
    ps

## Future Improvements

If further development were to continue, I would implement:

Support for background & execution

Output/input redirection (>, <)

Command pipelines (|)

Unit tests for command parsing and job management

Shell configuration file support (e.g., .myshrc)

## Contact

Feel free to reach out via apkinalbert@yandex.ru

## Repository

The source code for this project is available on GitHub: [https://github.com/apkinalbert/final_project](https://github.com/apkinalbert/final_project)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE.txt) file for details.