// Thomas McDowell
// 
// igrep.c is a command line tool built to imitate grep without regular expression capability.
// Behavior can be modified with the use of the following flags:
// -i: Ignore case
// -n: Print line numbers
// -h: Help


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

bool IGNORE_CASE = false;
bool LINE_NUMS = false;
bool HELP = false;


// Functions used in main
void strToLower(char *str);
void processFlags(int argc, char **argv);
void processLines(char *pattern);


int main(int argc, char **argv)
{
  // process arguments
  char *pattern = argv[1];
  processFlags(argc, argv);

  // handle flags 
  if (HELP) {
      printf("uh oh oopsies no helpies yet\n");
      exit(0);
  }

  if (IGNORE_CASE) {
    strToLower(argv[1]);
  }

  // Process and print lines that contain specified pattern (no regex allowed)
  processLines(pattern);
  exit(0);

}


// Convert a string to lowercase (Used for -i flag)
void strToLower(char *str)
{
  char *c = str;
      while (*c != '\0') { // until end of string 
          *c = tolower(*c);
          c++;
		}


}


// processLines takes a pattern then reads in a text file and searches its lines for a pattern.
// If the pattern is found in a line, the line is printed.
void processLines(char *pattern)
{
  char line[MAX_LINE_LENGTH];
  unsigned long int lineNum = 0;

  // for all lines in the file
  while ( fgets(line, MAX_LINE_LENGTH, stdin) ) {
      lineNum++;
      // If ignore case flag is used, make pattern and string cases the same
      if (IGNORE_CASE) {
        strToLower(line);
      }

      if (strstr(line, pattern) != NULL) {
          if (LINE_NUMS) {
              printf("%lu: %s", lineNum, line);
	  } else {
              printf("%s", line);
            }
      }

  }
}


// processFlags enables flags specified by user
void processFlags(int argc, char **argv)
{
  // process arguments
  for (int i=2; i<argc; i++) {
    char *a = argv[i];
    if (strncmp(a, "-i", 2) == 0) {
      IGNORE_CASE = true;
    }
    if (strncmp(a, "-n", 2) == 0) {
        LINE_NUMS = true;
    }
    if (strncmp(a, "-h", 2) == 0) {
        HELP = true;
    }

  }

}