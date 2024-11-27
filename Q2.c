#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h> // For wait()
#include "Q2.h"

#define PROMPT "enseash % "

void Q2() {
    char input[128];

    while (1) {
        // Display the prompt
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

        // Read the user command
        ssize_t user_read = read(STDIN_FILENO, input, sizeof(input) - 1);
        if (user_read > 0) {
            // Add a null terminator to the input string
            input[user_read - 1] = '\0';

            if (strcmp(input, "fortune") == 0) {
                int status;
                pid_t pid = fork(); // Create a child process

                if (pid > 0) {
                    // In the parent process: wait for the child to finish
                    wait(&status);
                } else if (pid == 0) {
                    // In the child process: execute the "fortune" command
                    execlp("fortune", "fortune", NULL); // No need for "-o", assuming the system has it installed
                    // If execlp fails, terminate the child process
                    _exit(1);
                }


                time_t now = time(NULL);
                struct tm *local = localtime(&now);
                char date[128];
                strftime(date, sizeof(date), "%a %b %d %H:%M:%S %Z %Y\n", local);


                write(STDOUT_FILENO, date, strlen(date));
            }
        }
    }
}
