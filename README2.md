# README2

* Lexcial Analyzer

Seperate input into token.

1. (\n) new line
2. (\t) discard white spaces (tabs and space)
3. (>) greater / redirect out
4. (<) lesser / redirect in
5. (>>) redirect append
6. (<<) redirect heredoc
7. (|) pipe
8. (=)
9. (/) for file directory
10. (+) will print out as + for string. Will add in $(5+10)
11. (!)
12. (`) backtick
13. (;) semi-colon To seperate into multi commands. eg: cmd1; cmd2; cmd3
14. (\) back slash
15. (.) dot
16. (?) question mark
17. (-) minus
18. ($) dollar sign For variable

Not sure if need or not
13. (~) tilde

Don't Need
20. (>&)
21. ampersand (&)  [Don't need]
22. (:) [Don't need]
23. (||) [Don't Need]
24. (*) [Don't need]

I don't need to implement: && and || and *

Sample commands

>pipe:
Used to pass the output of one command as input to another command.
ls -l | grep "file"

Count the number of lines in a file:
cat file.txt | wc -l

Count the number of lines in a file:
ls | sort

>Input redirect
Used to redirect input from a file to a command.
wc -l < file.txt

Display the contents of a file:
cat < file.txt

Pass the contents of a file as input to a command:
grep "pattern" < file.txt

>output redirect (>)
Used to redirect output from a command to a file, overwriting the file if it already exists.
echo "Hello, world!" > output.txt

Save the output of a command to a file:
ls -l > file_list.txt

Replace the contents of a file with new text
echo "New content" > file.txt

>append redirect (>>)
Used to redirect output from a command to a file, appending the output to the end of the file if it already exists.
echo "Goodbye, world!" >> output.txt

Append the output of a command to a file
date >> log.txt

Append the contents of one file to another file:
cat file1.txt >> file2.txt

>To Note:
Handle double quotes ("") and single quotes (''), which should escape special characters, beside $ for double quotes.

* Parser

Precedence climbing for the key characters
<https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing>

* signals

ctrl-C in an empty prompt should display a new line with a new prompt.
ctrl-\ in an empty prompt should not do anything.
ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.
The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.
ctrl-D in a prompt after you wrote some stuff should not do anything.
ctrl-\ in a prompt after you wrote some stuff should not do anything.
Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
Try ctrl-\ after running a blocking command like cat without arguments or grep “something“.
Try ctrl-D after running a blocking command like cat without arguments or grep “something“.
Repeat multiple times using different commands.
If something crashes, select the "crash" flag.

* built-ins:
Implement the following built in
— echo (option -n only)
— exit
— env (with no options or arguments)
— export (with no options)
— unset (with no options)
— cd
— pwd
