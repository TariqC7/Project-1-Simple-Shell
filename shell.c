#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;


int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];
    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    char *token;
    int status, index;
    int pid, parent_pid;
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // TODO:
        // 1. Tokenize the command line input (split it on whitespace)
        token = strtok(command_line, delimiters);
        index = 0;
        while (token != NULL) {
          arguments[index] = token;
          index++;
          token = strtok(NULL, delimiters);
        }
        
        pid = fork();
      
        // Child process
        if (pid == 0) {
          // 2. Create a child process which will execute the command line input
          execve(arguments[0], arguments, environ);
        }
        // Parent process
        else if (pid > 0) {
          // 3. The parent process should wait for the child to complete
          int status;
          wait(&status);
        }
    }
    
    // This should never be reached.
    return -1;
}

