# Minishell Project

## Requirements

1. Display prompt when waiting for new command
2. Working history
3. Serve and launch the right executable [based on path variable / relative / absolute path]
4. Avoid using more than 1 global variable [this is for signal only]
5. Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
6. Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
7. Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
8. Implement redirections:
    1. < should redirect input.
    2. > should redirect output.
    3. << should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    4. >> should redirect output in append mode.
9. Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
10. Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
11. Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
12. Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
13. In interactive mode:
    1. ctrl-C displays a new prompt on a new line.
    2. ctrl-D exits the shell.
    3. ctrl-\ does nothing.
14. Your shell must implement the following builtins
    1. echo with option -n
    2. cd with only a relative or absolute path
    3. pwd with no options
    4. export with no options
    5. unset with no options
    6. env with no options or arguments
    7. exit with no options	
built in
// echo
// exit
// env
// export
// unset
// pwd
// cd

The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.

## Conceptual

To do:
<https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf>

* Parser

Reads the command line such as “ls ­al” and puts it into a data structure called Command Table that will store the commands that will be executed.

* Executor

The executor will take the command table generated by the parser and for every SimpleCommand in the array it will create a new process. It will also if necessary create pipes to communicate the output of one process to the input of the next one. Additionally, it will redirect the standard input, standard output, and standard error if there are any redirections.

* Shell Subsystem

Other subsystems that complete your shell are:
● Environment Variables: Expressions of the form ${VAR} are expanded with the corresponding environment variable. Also the shell should be able to set, expand and print environment vars.
● Wildcards: Arguments of the form a*a are expanded to all the files that match them in the local directory and in multiple directories.
● Subshells: Arguments between `` (backticks) are executed and the output is sent as input to the shell.

* How it works

character goes into -> lexer -> parser -> wildchar and envar -> executor

cmd [arg] *[ | cmd [arg]* ]*  
          [ [> filename] [< filename] [ >& filename] [>> filename] [>>& filename] ]* [&]  
^Fig 4: Shell Grammar in Backus­Naur Form

This grammar is written in a format called “Backus­Naur Form”. For example cmd  [arg]*
means a command, cmd, followed by 0 or more arguments, arg. The expression [ | cmd
[arg]* ]* represents the optional pipe subcommands where there might be 0 or more of them.
The expression [>filename] means that there might be 0 or 1  >filename redirections. The
[&] at the end means that the & character is optional.  

Examples of commands accepted by this grammar are:
ls –al
ls –al > out
ls –al | sort >& out
awk –f x.awk | sort –u < infile > outfile &

The Command Table
The Command Table is an array of  SimpleCommand structs. A SimpleCommand struct contains members for the command and arguments of a single entry in the pipeline. The parser will look also at the command line and determine if there is any input or output redirection based on symbols present in the command (i.e. < infile, or > outfile).
Here is an example of a command and the Command Table it generates:
command
ls ­al | grep me > file1

simple command array
0: ls, -al, null
1: grep, me, null

io redirrectio
in: default, out:file1, err:default

For command table:
we will use the following classes: Command and SimpleCommand

// Command Data Structure
// Describes a simple command and arguments 
struct SimpleCommand {
        // Available space for arguments currently preallocated
        int _numberOfAvailableArguments;
        // Number of arguments
        int _numberOfArguments;
        // Array of arguments
        char ** _arguments;
        SimpleCommand();
        void insertArgument( char * argument );
};
// Describes a complete command with the multiple pipes if any
// and input/output redirection if any.
struct Command {
        int _numberOfAvailableSimpleCommands;
        int _numberOfSimpleCommands;
        SimpleCommand ** _simpleCommands;
        char * _outFile;
        char * _inputFile;
        char * _errFile;
        int _background;
        void prompt();
        void print();
        void execute();
        void clear();
        Command();
        void insertSimpleCommand( SimpleCommand * simpleCommand );
        static Command _currentCommand;
        static SimpleCommand *_currentSimpleCommand;
};

The constructor SimpleCommand::SimpleCommand constructs a simple empty command.
The method SimpleCommand::insertArgument( char * argument ) inserts a new argument
into the SimpleCommand and enlarges the _arguments array if necessary. It also makes sure
that the last element is NULL since that is required for the exec() system call.
The constructor Command::Command() constructs and empty command that will be populated with the method Command::insertSimpleCommand( SimpleCommand * simpleCommand). insertSimpleCommand also enlarges the array _simpleCommands if necessary. The variables _outFile, _inputFile, _errFile will be NULL if no redirection was done, or the name of the file they are being redirected to.
The variables  _currentCommand and _currentCommand are static variables, that is
there is only one for the whole class. These variables are used to build the Command and Simple command during the parsing of the command.
The Command and SimpleCommand classes implement the main data structure we will use in the shell

## Macbook Running Command For dev

1. Get ENTR
2. find . -name "*.c" | entr make

### Reference

1. Main Knowledge Source
<https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf>
<https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218>

2. AST Meaning
<https://en.wikipedia.org/wiki/Abstract_syntax_tree>

3. Sample shell
<https://github.com/Swoorup/mysh>

4. RTFM
<https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html>

5. Others
<https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J>

6. More resources to read
<https://www.gnu.org/software/libc/manual/html_node/Implementing-a-Shell.html>

7. others others. totally relevant
<https://lzcorp-my.sharepoint.com/personal/thelazyprogrammer_lzcorp_onmicrosoft_com/_layouts/15/onedrive.aspx?id=%2Fpersonal%2Fthelazyprogrammer%5Flzcorp%5Fonmicrosoft%5Fcom%2FDocuments%2FPublic%20ALX%20Resources&ga=1>

8. Minishell tester! How can we forget about this!
<https://github.com/LucasKuhn/minishell_tester>

9. Important on tokening
<https://liberius.notion.site/Tokenization-process-How-you-SHOULDN-T-do-lexer-for-minishell-d7d832fcba0d4955a159a40f9ece8110>