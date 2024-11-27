#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define WELCOME_MSG "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n"
#define PROMPT "enseash % "

int main() {
    char imput[128];

    //write the welcome message
    write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG));

    while (1) {
        write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

        //read the user command
        ssize_t user_read = read(STDIN_FILENO, imput, sizeof(imput));

        if (user_read > 0) {
            imput[user_read - 1] = '\0';// Add a null terminator to the input string

            if (strcmp(imput, "exit") == 0) {
                break;
            }
        }
    }
    return 0;
}
