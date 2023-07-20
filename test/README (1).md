# ALX Simple Shell Team Project

> This is an ALX collaboration project on Shell. We were tasked to create a simple shell that mimics the Bash shell. Our shell shall be called **hsh**

## Project was completed using

- C language
- Shell
- Betty linter

## General Requirement for project

- All files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Shell should not have any memory leaks
- No more than 5 functions per file
- All header files should be include guarded
- Write a README with the description of the project


## Description ##

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

### How **hsh** works
* Prints a prompt and waits for a command from the user
* Creates a child process in which the command is checked
* Checks for built-ins, aliases in the PATH, and local executable programs
* The child process is replaced by the command, which accepts arguments
* When the command is done, the program returns to the parent process and prints the prompt
* The program is ready to receive a new command
* To exit: press Ctrl-D or enter "exit" (with or without a status)
* Works also in non interactive mode

### Compilation

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`


Example:
```
$ echo "echo 'hello'" | ./hsh
'hello'
$
```

If **hsh** is invoked with standard input connected to a terminal (determined by [isatty](https://linux.die.net/man/3/isatty)(3)), an *interactive* shell is opened. When executing interactively, **hsh** displays the prompt `$ ` when it is ready to read a command.

Example:
```
$./hsh
$
```

Alternatively, if command line arguments are supplied upon invocation, **hsh** treats the first argument as a file from which to read commands. The supplied file should contain one command per line. **hsh** runs each of the commands contained in the file in order before exiting.

### Exit Status

**hsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

User hits `Ctrl+d` in the third line.
```
$ ./hsh
$ ^C
$ ^C
$
```

Example:
```
$ ./hsh
$ pwd
/home/projects/alx/simple_shell
$ cd ../
$ pwd
/home/projects/alx

Example:
```
$ ./hsh
$ exit
```

### What we learned:
* How a shell works and finds commands
* Creating, forking and working with processes
* Executing a program from another program
* Handling dynamic memory allocation in a large program
* Pair programming and team work
* Building a test suite to check our own code


## Authors ##

👤 **THANKGOD EBIRI**

👤 **OKEOMASILACHI ONYEDIBIA**
