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
        return EXIT_FAILURE;
    }
  }

  int startIndex = (iflag || cflag) ? 3 : 2;
  int patternIndex = startIndex - 1;

  for (int j = startIndex; j < argc; j++) {
    FILE *f = fopen(argv[j], "r");

    if (f) {
      char buffer[500] = { 0 };
      while (fgets(buffer, 500, f)) {
        lines++;
        if (iflag ? strcasestr(buffer, argv[patternIndex])
                  : strstr(buffer, argv[patternIndex])) {
          printf("%s: ", argv[j]);
          fputs(buffer, stdout);
        }
      }
    } else {
      fprintf(stderr, "Unable to open file\n");
      perror("Error opening file\n");
    }
    fclose(f);
    if (ferror(f)) {
      fprintf(stderr, "Error reading file\n");
    }
  }

  if (cflag) {
    printf("Total lines scanned: %d\n", lines);
  }

  return EXIT_SUCCESS;
}