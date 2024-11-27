//
// Created by grimont on 27/11/24.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "Q3.h"

#define PROMPT "enseash % "


void Q3() {
    char input[128];
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