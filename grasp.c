#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>


int main(int argc, char *argv[argc + 1]) {
    for (int j=2; j<argc; j++) {
        FILE *f = fopen(argv[j], "r");

        if (f) {
            char buffer[500] = { 0 };
            while (fgets(buffer, 500, f)) {
                if (strstr(buffer, argv[1])) {
                    printf("%s: ", argv[j]);
                    fputs(buffer, stdout);
                }
            }
        }
        else {
            perror("Couldn't open file");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;

}