#include "Q7.h"
#include "Q5.h"

// Definition of global variables (from Q5.h)
extern struct timespec start_time;
extern struct timespec end_time;

// Function to display messages with exit code, signal, and execution time
void display_mess3(const char *text, int val1, int val2) {
    char buff[MAXSIZE];
    sprintf(buff, text, val1, val2);
    write(STDOUT_FILENO, buff, strlen(buff));
}

void Q7() {
    char input[MAXSIZE];
    char *args[MAXSIZE / 2 + 1]; // Array to hold command and arguments
    char *input_file = NULL;
    char *output_file = NULL;

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

        // Check for redirection symbols and extract filenames
        input_file = NULL;
        output_file = NULL;

        // Check for output redirection (>)
        char *output_redirect = strstr(input, ">");
        if (output_redirect != NULL) {
            *output_redirect = '\0'; // Null-terminate the command part
            output_file = strtok(output_redirect + 1, " \t"); // Get the file name
        }

        // Check for input redirection (<)
        char *input_redirect = strstr(input, "<");
        if (input_redirect != NULL) {
            *input_redirect = '\0'; // Null-terminate the command part
            input_file = strtok(input_redirect + 1, " \t"); // Get the file name
        }

        // Tokenize the command and arguments
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
            // Handle input redirection
            if (input_file != NULL) {
                int input_fd = open(input_file, O_RDONLY);
                if (input_fd == -1) {
                    perror("Error opening input file");
                    exit(1);
                }
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // Handle output redirection
            if (output_file != NULL) {
                int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (output_fd == -1) {
                    perror("Error opening output file");
                    exit(1);
                }
                dup2(output_fd, STDOUT_FILENO);
                close(output_fd);
            }

            // Execute the command with arguments
            execvp(args[0], args);
            perror("Command not found");
            exit(1);
        } else {
            // Start the timer, wait for the child process to finish, and stop the timer
            start_timer();
            wait(&status);
            end_timer();

            // Calculate the elapsed time
            int elapsed_time = get_time();

            // Display results
            if (WIFEXITED(status)) {
                display_mess3(MSG_EXIT, WEXITSTATUS(status), elapsed_time); // Exit status + time
            } else if (WIFSIGNALED(status)) {
                display_mess3(MSG_SIGN, WTERMSIG(status), elapsed_time); // Signal + time
            }
        }
    }
}
