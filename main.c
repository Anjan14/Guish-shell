#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // Access to the POSIX operating system API
#include <sys/wait.h> // Wait library for process termination and wait functions
#include <errno.h>    // Library for error number definitions
//------------------------------------X------------------------------------------|
/*
    1. Define a constant for the maximum number of history entries
    2. History size of 10 is chosen for simplicity
    3. Allows for straightforward implementation of adding and removing
    4. Also displays commands without excessive complexity
*/
#define MAX_HISTORY 10
//------------------------------------X------------------------------------------|
/*
    1. Define a constant for the maximum length of a command
    2. 1024 bytes-->1 kilobyte-->Standard buffer size
    3. Large enough for most commands
    4. Efficient for memory allocation and prevents buffer overflow
*/
#define MAX_COMMAND_LENGTH 1024
//------------------------------------X------------------------------------------|
/*
    1. Declare an array to hold the history of commands
    2. Max history size is 10--> provides constant time access (efficient)
    3. Supports the implementation of hist and r n commands
*/
char *history[MAX_HISTORY];
// Initialize history count to zero(0)
int history_count = 0;
//------------------------------------X------------------------------------------|
// Function to add a command to the history
void add_to_history(const char *command) {
    /*
        1. If there is space in the history array
        2. Only adds a new command given available space
        3. Maintains the history size of 10
    */
    if (history_count < MAX_HISTORY) 
    {
        /*
            1. Duplicate the command and add it to the history
            2. strdup function allocates memory and creates a copy of the given command string
            3. History array stores independent copies of each command
            4. Can't do pointers to the original strings
            5. Because, they may be modified or deallocated somewhere else in the program
        */
        history[history_count++] = strdup(command);
    } 
    else 
    {
        /*
            1. Free the memory of the oldest command to make space for new command
            2. Prevents memory leak by releasing oldest command
        */
        free(history[0]);
        // Shift all commands in the history array to the left
        for (int index = 1; index < MAX_HISTORY; index++) 
        {
            history[index - 1] = history[index];
        }
        /*
            1. Add the new command to the end of the history array
            2. Ensures most recent command is stored at the end of the array
        */
        history[MAX_HISTORY - 1] = strdup(command);
    }
}
//------------------------------------X------------------------------------------|
// Function to print the command history
void print_history() {
    /*
        1. Loop through the history array 
        2. And print each command with its index
    */
    for (int index = 0; index < history_count; index++) 
    {
        printf("%d %s\n", index + 1, history[index]);
    }
}
//------------------------------------X------------------------------------------|
// Function to execute commands
void execute_command(char *command) {
    // Define an array to hold command arguments
    char *argv[MAX_COMMAND_LENGTH];
    // Initialize argument count to zero(0)
    int argc      = 0;
    // Tokenize the command string using space as delimiter
    char *token   = strtok(command, " ");
    //Loop through all tokens
    while (token != NULL) 
    {
        // Add the token to the arguments array
        argv[argc++] = token;
        // Get the next token
        token        = strtok(NULL, " ");
    }
    // Null terminate the arguments array
    argv[argc] = NULL;

    // If no command entered, return
    if (argc == 0) return;

    // Check if the command is exit
    if (strcmp(argv[0], "exit") == 0) 
    {
        // If yes, exit the shell
        exit(0);
    } 
    // Check is the command is hist
    else if (strcmp(argv[0], "hist") == 0) 
    {
        // If yes, print the command history and return
        print_history();
        return;
    } 
    // Check if the command is r
    else if (strcmp(argv[0], "r") == 0) 
    {
        // Determine the history index to run
        int hist_index = (argc == 1) ? history_count - 1 : atoi(argv[1]) - 1;
        // Validate the history index
        if (hist_index < 0 || hist_index >= history_count) 
        {
            // Print error if the index is invalid and return
            printf("No such command in history.\n");
            return;
        }
        // Print the command to be executed
        printf("%s\n", history[hist_index]);
        // Copy the command from history
        strcpy(command, history[hist_index]);
        // Add the command to history
        add_to_history(command);
        // Execute the command recursively
        execute_command(command);
        return;
    }

    // Add the command to history
    add_to_history(command);

    //Create a new process
    pid_t pid = fork();
    if (pid < 0) 
    {
        // Print error if fork fails
        perror("Fork failed");
    } 
    else if (pid == 0) 
    {
        /*
            1. In the child process, execute the command using execvp
            2. execvp replaces the current process image with a new one
        */
        execvp(argv[0], argv);
        /*
            1. If execvp fails, print error message
            2. errno contains the error code indicating why execvp failed
        */
        printf("The program seems missing. Error code is: %d\n", errno);
        /*
            1. Exit the child process with the error code
            2. Ensures child process doesn't continue running the shell code
        */
        exit(errno);
    } 
    else 
    {
        // In the parent process, wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);
        // Check if the child process exited with an error
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
        {
            // Print the error code
            printf("The program exited with error: %d\n", WEXITSTATUS(status));
        }
    }
}
//------------------------------------X------------------------------------------|
int main() {
    // Declare a buffer to hold the command input
    char command[MAX_COMMAND_LENGTH];
    // Infinite loop to continuously accept commands
    while (1) 
    {
        // Print the shell prompt
        printf("guish> ");
        // Read the command from standard input
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) 
        {
            // Break the loop if end of input is reached
            break;
        }
        // Remove the new line character from the command
        command[strcspn(command, "\n")] = '\0';
        // Execute the command
        execute_command(command);
    }
    // If execution is successful-->
    return 0;
}