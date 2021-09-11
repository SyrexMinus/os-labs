#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main () {
    while(1) {
        char input[1024];
        char *command[64];
        for (int i = 0; i < 64; i++) {
            command[i] = NULL;
        }
        int is_background = 0;

        /* read command */
        printf("> ");
        /* read from stdin
           note the `sizeof char`, if you need to change the size of `word`,
           you won't have to change this line. */
        fgets(input, sizeof input, stdin);

        /* initialize parser */
        char delim[] = " \n";
        char *tok = strtok(input, delim);

        /* parse commands */
        for (int i = 0; tok != NULL; i++) {
            if(tok[0] == '&') {
                is_background = 1;
            }
            else {
                command[i] = malloc(strlen(tok) + 1);
                strcpy(command[i], tok);
            }

            /* get next token*/
            tok = strtok(NULL, delim);
        }

        /* execute command in new process */
        pid_t childPid = fork();
        if(childPid == 0) {
            if(is_background) {
                daemon(0, 0);
            }
            execvp(command[0], command);
            return 0;
        }
        else {
            int returnStatus;
            waitpid(childPid, &returnStatus, 0);  // Parent process waits here for child to terminate.
        }
    }

    return 0;
}