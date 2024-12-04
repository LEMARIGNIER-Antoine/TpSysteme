#include "Q4.h"

void display_mess(char *text, int val) {
    char buff[MAXSIZE];
    sprintf(buff, text, val);
    write(STDOUT_FILENO, buff, strlen(buff));
}

void Q4() {
    char input[128];
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

        //  "exit" command
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, BYE, strlen(BYE));
            exit(0);
        }

        pid_t pid = fork();
        int status = 0;

        if (pid == -1) { // Fork error
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {
            // Execute the command in the child process
            execlp(input, input, NULL);
            perror("Command not found");
            exit(1);
        } else {

            wait(&status);// Parent process waits for child to finish

            if (WIFEXITED(status)) { // Display the exit status or signal information
                display_mess(MSG_EXIT, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                display_mess(MSG_SIGN, WTERMSIG(status));
            }
        }
    }
}
