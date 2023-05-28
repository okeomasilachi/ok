# Custom Shell

This project is a custom shell implementation written in C. The shell provides a command-line interface for executing commands and supports basic functionality such as tokenization, command parsing, and command execution.

## Features

- **Tokenization**: The shell includes a tokenizer that splits a given string into tokens based on specified delimiters.
- **Command Parsing**: The shell parses the input command into individual tokens, allowing for the extraction of command arguments and options.
- **Executable Lookup**: The shell searches for the executable file corresponding to a given command in the system's PATH environment variable.
- **Command Execution**: The shell executes the specified command by forking a child process and invoking the appropriate executable.

## Getting Started

To compile and run the shell, follow these steps:

1. Clone the repository: `git clone https://github.com/ok`
2. Navigate to the project directory: `cd ok`
3. Compile the source code: `gcc -Wall -pedantic -Werror -Wextra -std=gnu89 *.c -g -o shell`
4. Run the shell: `./shell`

## Usage

Once the shell is running, you can enter commands and interact with the shell. The shell provides a command prompt where you can enter commands, and it will execute them accordingly.

Example usage:
$ ls -l
$ cd /path/to/directory
$ echo "Hello, World!"

## Limitations

- The shell currently supports a limited set of commands and options.
- Error handling and validation of user input are minimal.
- Advanced features such as piping, redirection, and background processes are not implemented.

## Contributing

Contributions to this project are welcome. If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for more information.
