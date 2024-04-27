# TO DO

1. To check on lexical file:
Double check whether im copying everything correctly or not.

2. To check parser
cat << EOF > file | wc -c | tr -d " " > file2 | ls -l | wc -c

cat << EOF > file | wc -c | tr -d " " > file2 | ls -l | wc -c | grep "mini" < TODO.md; ls-l

cat << EOF > file | wc -c | tr -d " " > file2 | ls -l | wc -c | echo $HOME | grep "mini" < TODO.md; ls-l | echo $HOME

grep 'pattern' << EOF
line 1 with pattern
line 2 without pattern
line 3 with pattern again
EOF

// sample AST to be created
//                       __PIPELINE__
//                  ___/              \____
//                 /                       \
//         COMMAND                    __PIPELINE _
//       /        \                  /             \
// ARGUMENTS   REDIRECTIONS      COMMAND         _COMMAND__
//     |          |     |           |           /            \
//    cat        <<     >       ARGUMENTS    ARGUMENTS   REDIRECTIONS
//                |     |         |   |      |   |   |        |
//              "..."  file      wc  -c      tr  -d " "       >
//                                                            |
//                                                          file2
// cat << EOF > file | wc -c | tr -d " " > file2

PIPELINE, COMMAND, ARGUMENT, REDIRECTION

How the above is borken down:
cat << EOF > file | wc -c | tr -d " " > file2

Left half:
> Command
Arguments: Cat
Redirections: << EOF
Redirections: > file

Right half:
> Command 1
> Argument
Argument: wc -c [Whole and not broken down]
> Command 2
> Argument
Argument: tr -d "" [Whole and not broken down]
Redirect: > file2

* Look for any pipe. If there exist, it should be the "root"
* After pipe will always be a command
* Arguments on the left, redirects on the right

other commands
date "+%Y-%m-%d %H:%M:%S" > file | wc -l | tr -d " " > file2

echo "New line" >> file | wc -c | tr -d " " > file2

sed 's/old/new/g' file > file | wc -l | tr -d " " > file2

// This got issue. End with redirect but why?
grep "error" file | wc -l > file2

// This got issue. End with redirect but why?
sort file | uniq -c > file2

// This does not work due to no pipes present.
stat -c "%a" file > file2
..
..
3. CD

* tilde [~..]
* cd [To return to home]
..
.

4. EXPORT & UNSET

Eg:
// Export to the environment
export MY_VAR="Hello"

// You can grep from environment to see it.
// Alternatively you can env and slowly find
env | grep MY_VAR

// Unset to remove it from the env
unset MY_VAR

// You can grep from environment to see it.
// Alternatively you can env and slowly find
// Should not be able to find MY_VAR
env | grep MY_VAR

How to do it?

// Set the environment variable MY_VARIABLE to "Hello, World!"
setenv("MY_VARIABLE", "Hello, World!", 1);

 // Unset the environment variable MY_VARIABLE
unsetenv("MY_VARIABLE");

5. To do error handling for all of them

6. Handling single and double quotations

7. Finding of env variable and substituting

8. Figure out whether i need to handle parsing ';'

Logic:
lexical -> parser -> sub -> replace empty str

Heredoc [have the existing code to move over]

program execution [have the existing code to run the program]
but need to do parallel

signal

Pipes
