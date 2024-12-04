#include "Q6.h"

void Q6() {
    char input[MAXSIZE];
    char *args[MAXSIZE / 2 + 1]; // Array to hold command and arguments

    while (1) {
        // Display prompt
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

        // Read user input
        ssize_t user_read = read(STDIN_FILENO, input, sizeof(input) - 1);
        if (user_read == -1) {
            perror("Error reading input");
            exit(1);
        }

        input[user_read - 1] = '\0'; // Null-terminate the input

        // Handle "exit" command
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, BYE, strlen(BYE));
            exit(0);
        }

        // Tokenize the input into command and arguments
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL && arg_count < MAXSIZE / 2) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Null-terminate the argument list

        pid_t pid = fork();
        int status = 0;

        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }

        if (pid == 0) {
            // Execute the command with arguments
            execvp(args[0], args);
            perror("Command not found");
            exit(1);
        } else {
            // Parent process waits for the child to finish
            wait(&status);
        }
    }
}
