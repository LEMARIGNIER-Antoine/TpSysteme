#include "Q5.h"

struct timespec start_time;
struct timespec end_time;

void display_mess2(const char *text, int val1, int val2) { // We adapt the function before to add the time
    char buff[MAXSIZE];
    sprintf(buff, text, val1, val2);
    write(STDOUT_FILENO, buff, strlen(buff));
}

void start_timer() {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void end_timer() {
    clock_gettime(CLOCK_MONOTONIC, &end_time);
}

int get_time() {
    return (int)((end_time.tv_sec - start_time.tv_sec) * 1000 +
                 (end_time.tv_nsec - start_time.tv_nsec) / 1e6);
}

void Q5() {
    char input[MAXSIZE];
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

        // "exit" command
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO, BYE, strlen(BYE));
            exit(0);
        }

        pid_t pid = fork();
        int status = 0;

        if (pid == -1) {
            perror("Fork error");
            exit(1);
        }

        if (pid == 0) {
            execlp(input, input, NULL);
            perror("Command not found");
            exit(1);
        } else {

            start_timer();
            wait(&status);
            end_timer();

            int elapsed_time = get_time(); // get time

            // Display results
            if (WIFEXITED(status)) {
                display_mess2(MSG_EXIT, WEXITSTATUS(status), elapsed_time); // displaying exit with the time delayed
            } else if (WIFSIGNALED(status)) {
                display_mess2(MSG_SIGN, WTERMSIG(status), elapsed_time);
            }
        }
    }
}
