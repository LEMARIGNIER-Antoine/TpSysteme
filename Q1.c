//
// Created by grimont on 27/11/24.
//
// Created by grimont on 27/11/24.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Q1.h" // Include the corresponding header file

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "

void Q1() {
    char input[128];

    // Write the welcome message
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));

    while (1) {

        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

        // Read the user command
        ssize_t user_read = read(STDIN_FILENO, input, sizeof(input) - 1);

        if (user_read > 0) {
            // Add a null terminator to the input string
            input[user_read - 1] = '\0';


            if (strcmp(input, "exit") == 0) {
                break; // Exit the loop
            }
        }
    }
}
