#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>



int main(int argc, char *argv[argc + 1]) {
    int iflag, cflag, ch, lines;

    iflag = 0;
    cflag = 0;
    lines = 0;

    while ((ch = getopt(argc, argv, "ic")) != -1) {
        switch (ch) {
            case 'i':
                iflag = 1;
                break;
            case 'c':
                cflag = 1;
                break;
            case '?':
            default:
                printf("default");
        }
    }
    //argc -= optind;
    //argv += optind;

    for (int j=(iflag || cflag) ? 3 : 2; j<argc; j++) {
        FILE *f = fopen(argv[j], "r");

        if (f) {
            char buffer[500] = { 0 };
            while (fgets(buffer, 500, f)) {
                lines++;
                if (strstr(buffer, argv[j-1])) {

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

    if (cflag) {
        printf("Total lines scanned: %d\n", lines);
    }

    return EXIT_SUCCESS;

}