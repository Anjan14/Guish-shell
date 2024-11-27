# Guish-shell

Guish-shell is a custom Unix shell developed in C language. This project aims to build a command-line interface (CLI) shell that supports basic commands, history management, and error handling.

## Features

- **Basic Commands**: Execute standard Unix commands.
- **History Management**: Keep track of previously executed commands.
- **Error Handling**: Handle errors gracefully and provide meaningful messages.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS, etc.)
- GCC (GNU Compiler Collection)

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/Anjan14/guish-shell.git
    cd guish-shell
    ```

2. Compile the source code:
    ```sh
    gcc -o guish guish.c
    ```

3. Run the shell:
    ```sh
    ./guish
    ```

## Usage

Once the shell is running, you can enter commands just like you would in a standard Unix shell. For example:

```sh
guish> ls
guish> pwd
guish> echo "Hello, World!"
