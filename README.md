# Minimal Unix Shell

A minimal Unix shell written in C that implements basic shell functionalities such as command execution, process management, built-in commands (`cd`, `exit`, `help`), background job support, and signal handling.

## Features

- Interactive command input and execution using `fork()` and `exec()`
- Built-in commands: `cd`, `exit`, `help`
- Signal handling for `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP)
- Basic job control: `jobs`, `fg`, `bg`

## Motivation

This project facilitates a deeper understanding of Unix system calls, process management, and the interaction between a shell and the operating system at a low level. It serves as an effective practical exercise for exploring user-to-OS communication mechanisms.

## Project Structure

- src/ — Contains all the source code files. Each module or component is separated into its own file or subdirectory to improve readability and manageability.

- include/ — Header files (if applicable) are stored here, defining interfaces and shared declarations used throughout the project.

- Makefile — Compilation rules for building the shell

- README.md — Project documentation (you’re reading it!)


## Build & Run

1. Compile the shell using `make`:
    ```bash
    make
   
2. Run the shell:
    ```bash
    ./mysh

3. Use it like a normal shell. For example:
    ```bash
    ls
    cd ..
    exit
and so on...

## Future Improvements

Add support for pipes and input/output redirection

Enhance signal handling and job control features

## Contact

Feel free to reach out via apkinalbert@yandex.ru

## Repository

The source code for this project is available on GitHub: [https://github.com/apkinalbert/final_project](https://github.com/apkinalbert/final_project)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE.txt) file for details.