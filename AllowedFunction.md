
# Allowed function

Here's an explanation of each function mentioned:

All these for storing of command line && command

1. `readline`: Reads a line of text from the user, providing line-editing capabilities.

2. `rl_clear_history`: Clears the history list maintained by `readline`.

3. `rl_on_new_line`: Performs actions that should be done when a new line is encountered.

4. `rl_replace_line`: Replaces the contents of the current line.

5. `rl_redisplay`: Updates the display to reflect any changes made to the current line.

6. `add_history`: Adds a line to the history list.

7. `printf`: Prints formatted output to the standard output stream.

8. `malloc`: Allocates memory on the heap.

9. `free`: Deallocates memory allocated by `malloc`.

10. `write`: Writes data to a file descriptor.

11. `access`: Checks file access permissions.

12. `open`: Opens a file or device.

13. `read`: Reads data from a file descriptor.

14. `close`: Closes a file descriptor.

15. `fork`: Creates a new process by duplicating the existing process.

16. `wait`, `waitpid`, `wait3`, `wait4`: Wait for child processes to finish.

17. `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`: Handle signals.

18. `exit`: Exits the current process.

19. `getcwd`: Gets the current working directory.

20. `chdir`: Changes the current working directory.

21. `stat`, `lstat`, `fstat`: Get file status.

22. `unlink`: Deletes a name from the file system.

23. `execve`: Executes a program.

24. `dup`, `dup2`: Duplicates file descriptors.

25. `pipe`: Creates a pipe.

26. `opendir`, `readdir`, `closedir`: Open, read, and close directory streams.

27. `strerror`: Returns a string describing an error code.

28. `perror`: Prints a description for the last error occurrence.

29. `isatty`: Tests whether a file descriptor refers to a terminal.

30. `ttyname`: Returns the name of the terminal connected to a file descriptor.

31. `ttyslot`: Gets the slot number of the current terminal in the terminal table.

32. `ioctl`: Performs I/O control operations on a file descriptor.

33. `getenv`: Retrieves the value of an environment variable.

34. `tcsetattr`, `tcgetattr`: Get and set terminal attributes.

35. `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`: Functions for dealing with terminal capabilities using the terminfo database.

# include <stdio.h>

# include <stdlib.h>

# include <unistd.h>

# include <fcntl.h>

# include <signal.h>

# include <string.h>

# include <sys/types.h>

# include <sys/stat.h>

# include <dirent.h>

# include <termios.h>

# include <curses.h>

# include <term.h>

# include <errno.h>

/*Function prototypes*/

/*Reads a line of text from the user, providing line-editing capabilities*/
char *readline(const char*prompt);

/*Clears the history list maintained by readline*/
void rl_clear_history(void);

/*Performs actions that should be done when a new line is encountered*/
void rl_on_new_line(void);

/*Replaces the contents of the current line*/
void rl_replace_line(const char *text, int clear_undo);

/*Updates the display to reflect any changes made to the current line*/
void rl_redisplay(void);

/*Adds a line to the history list*/
void add_history(const char *line);

/*Prints formatted output to the standard output stream*/
int printf(const char *format, ...);

/*Allocates memory on the heap*/
void *malloc(size_t size);

/*Deallocates memory allocated by malloc*/
void free(void *ptr);

/*Writes data to a file descriptor*/
ssize_t write(int fd, const void *buf, size_t count);

/*Checks file access permissions*/
int access(const char *pathname, int mode);

/*Opens a file or device*/
int open(const char *pathname, int flags, mode_t mode);

/*Reads data from a file descriptor*/
ssize_t read(int fd, void *buf, size_t count);

/*Closes a file descriptor*/
int close(int fd);

/*Creates a new process by duplicating the existing process*/
pid_t fork(void);

/*Wait for child processes to finish*/
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int*status, int options);
pid_t wait3(int *status, int options, struct rusage*rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage*rusage);

/*Handle signals*/
void (*signal(int signum, void (*handler)(int)))(int);
int sigaction(int signum, const struct sigaction *act, struct sigaction*oldact);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t*set, int signum);
int kill(pid_t pid, int sig);

/*Exits the current process*/
void exit(int status);

/*Gets the current working directory*/
char *getcwd(char*buf, size_t size);

/*Changes the current working directory*/
int chdir(const char *path);

/*Get file status*/
int stat(const char *pathname, struct stat*statbuf);
int lstat(const char *pathname, struct stat*statbuf);
int fstat(int fd, struct stat *statbuf);

/*Deletes a name from the file system*/
int unlink(const char *pathname);

/*Executes a program*/
int execve(const char *pathname, char*const argv[], char *const envp[]);

/*Duplicates file descriptors*/
int dup(int oldfd);
int dup2(int oldfd, int newfd);

/*Creates a pipe*/
int pipe(int pipefd[2]);

/*Open, read, and close directory streams*/
DIR *opendir(const char*name);
struct dirent *readdir(DIR*dirp);
int closedir(DIR *dirp);

/*Returns a string describing an error code*/
char *strerror(int errnum);

/*Prints a description for the last error occurrence*/
void perror(const char *s);

/*Tests whether a file descriptor refers to a terminal*/
int isatty(int fd);

/*Returns the name of the terminal connected to a file descriptor*/
char *ttyname(int fd);

/*Gets the slot number of the current terminal in the terminal table*/
int ttyslot(void);

/*Performs I/O control operations on a file descriptor*/
int ioctl(int fd, unsigned long request, ...);

/*Retrieves the value of an environment variable*/
char *getenv(const char*name);

/*Get and set terminal attributes*/
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int tcgetattr(int fd, struct termios*termios_p);

/*Functions for dealing with terminal capabilities using the terminfo database*/
int tgetent(char *bp, const char*name);
int tgetflag(const char *id);
int tgetnum(const char*id);
char *tgetstr(const char*id, char **area);
char *tgoto(const char*cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
