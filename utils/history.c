#include "utils.h"

//to do:
// 1. Change back to rl_clear_history

// void initialize_readline()
// {
// 	// rl_clear_history();
// 	clear_history();
// }

// void	clearhistory()
// {
// 	// rl_clear_history();
// 	clear_history();
// }

// /*Reads a line of text from the user, providing line-editing capabilities*/
// /*Functionality: readline reads a line from the standard input and returns it, 
// allowing the user to edit the line with various key bindings.
// It provides a wealth of line-editing features, such as moving the cursor or deleting words.
// Usage: The function is called with a prompt string, which it displays before the user begins input. 
// The returned line does not include the trailing newline character and must be freed by the user to avoid memory leaks.
// */
// char *readline(const char*prompt);
// // char *input = readline("Enter command: ");
// // if (input) {
// //     printf("You entered: %s\n", input);
// //     free(input);  // Freeing the memory allocated by readline
// // }

// /*Clears the history list maintained by readline*/
// /*
// Functionality: This function clears the entire history maintained by the Readline library. 
// This is useful in scenarios where the history needs to be wiped clean, for security or privacy reasons, for example.
// Usage: It does not take any arguments and does not return any value.
// */
// // void rl_clear_history(void);
// // rl_clear_history();

// /*Performs actions that should be done when a new line is encountered*/
// /*
// Functionality: This function should be called whenever a newline is output to the screen while using Readline. 
// It tells Readline that the cursor is at the start of a new line, which helps maintain the correct display state.
// Usage: Typically used in applications that manually handle output while also using Readline for input.
// */
// void rl_on_new_line(void);
// // printf("\nNew output generated:\n");
// // rl_on_new_line();

// /*Replaces the contents of the current line*/
// /*Functionality: rl_replace_line replaces the contents of the current line buffer in Readline. 
// This is useful for programmatically changing the input line based on certain conditions.
// Usage: It takes two parameters: the new text for the line and an integer to reset the undo history.*/
// void rl_replace_line(const char *text, int clear_undo);
// // rl_replace_line("New Command", 0);

// /*Updates the display to reflect any changes made to the current line*/
// /*
// Functionality: Forces Readline to update the display based on the current contents of the line buffer.
// This function is essential after making changes to the line buffer programmatically (such as with rl_replace_line).
// Usage: It redraws the line to reflect changes.
// */
// void rl_redisplay(void);
// // rl_replace_line("Updated command", 1);
// // rl_redisplay();


// /*Adds a line to the history list*/
// /*
// Functionality: Adds a line to the history maintained by Readline. This allows users to scroll back through previous commands they've entered.
// Usage: The line to be added is passed as an argument. It's typically used after successfully processing a command to record it in history.
// */
// void add_history(const char *line);
// // if (input && *input) {  // Ensuring input is not empty
// //     add_history(input);
// // }
