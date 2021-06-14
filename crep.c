// Thomas McDowell
//
// crep.c is a command line tool built to imitate grep without regular
// expression capability. Behavior can be modified with the use of the following
// flags: -i: Ignore case -n: Print line numbers -h: Help

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

bool IGNORE_CASE = false;
bool LINE_NUMS = false;
bool HELP = false;
bool GOT_PATTERN = false;

// Functions used in main
void strToLower(char *str);
char *processArgs(int argc, char **argv);
void processLines(char *pattern);

int main(int argc, char **argv) {
  // Process arguments
  char *pattern = processArgs(argc, argv);

  // Handle flags
  if (HELP) {
    printf("Usage: ./crep [OPTION]... PATTERN FILE\n");
    printf("Search for PATTERN in FILE\n");
    printf("Example: ./crep -n \"whale\" <MobyDick.txt\n\n");
    printf("Options:\n");
    printf("    -i    PATTERN ignores case\n");
    printf("    -n    print line number with output lines\n");
    printf("    -h    help\n");
    exit(0);
  }

  if (IGNORE_CASE) {
    strToLower(pattern);
  }

  // Process and print lines that contain specified pattern (no regex allowed)
  processLines(pattern);
  exit(0);
}

// Convert a string to lowercase (Used for -i flag)
void strToLower(char *str) {
  char *c = str;
  while (*c != '\0') { // until end of string
    *c = tolower(*c);
    c++;
  }
}

// processArgs processes user arguments
char *processArgs(int argc, char **argv) {
  char *pattern;
  // process arguments
  if (argc < 2) {
    HELP = true;
  }
  // For each argument
  for (int i = 1; i < argc; i++) {
    char *argument = argv[i];
    // Process valid flags, print error message if invalid flag is detected
    if (*argument == '-') {
      argument++;
      while (*argument != '\0') {
        if (*argument == 'i') {
          IGNORE_CASE = true;
        } else if (*argument == 'n') {
          LINE_NUMS = true;
        } else if (*argument == 'h') {
          HELP = true;
        } else {
          printf("ERROR: invalid flag detected\n");
          exit(1);
        }
        argument++;
      }
    }

    // Pattern will be first arg that does not start with '-'
    else if (GOT_PATTERN == false) {
      pattern = argument;
      GOT_PATTERN = true;
    }
  }
  return pattern;
}

/* processLines takes a pattern then reads in a text file and searches its lines
   for a pattern. If the pattern is found in a line, the line is printed. */
void processLines(char *pattern) {
  char line[MAX_LINE_LENGTH];
  unsigned long int lineNum = 0;

  // For all lines in the file
  while (fgets(line, MAX_LINE_LENGTH, stdin)) {
    lineNum++;
    /* If ignore case flag is used, create a copy of each line to print
       and make every char lowercase */
    if (IGNORE_CASE) {
      char lineCopy[strlen(line)];
      strcpy(lineCopy, line);
      strToLower(line);

      // Search lines for pattern and print line if pattern is found
      if (strstr(line, pattern) != NULL) {
        if (LINE_NUMS) {
          printf("%lu:%s", lineNum, lineCopy);
        } else {
          printf("%s", lineCopy);
        }
      }
    }
    // If ignore case flag is not used
    else if (strstr(line, pattern) != NULL) {
      if (LINE_NUMS) {
        printf("%lu:%s", lineNum, line);
      } else {
        printf("%s", line);
      }
    }
  }
}
