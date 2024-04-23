# TO DO

1. To check on lexical file:
Double check whether im copying everything correctly or not.

2. To check parser
cat << EOF > file | wc -c | tr -d " " > file2

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

4. Working history not done as well