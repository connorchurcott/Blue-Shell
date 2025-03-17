#define _POSIX_C_SOURCE 1
#include "input.h"
#include <string.h>

void getInput(char *readBuffer, int size) {
  ssize_t bytesRead = read(0, readBuffer, size - 1);

  if (bytesRead > 0 && readBuffer[bytesRead - 1] == '\n') {
    readBuffer[bytesRead - 1] = '\0';
  }

  if (bytesRead <= 0) {
    char *readError = FORMAT_MSG("shell", READ_ERROR_MSG);
    write(2, readError, strlen(readError));
  }
}

void tokenizeInput(char *input, char *output[]) {

  char *delim = " \n";
  char *saveptr;

  char *token = strtok_r(input, delim, &saveptr);

  int i = 0;
  while (token != NULL) {
    output[i] = token;
    i++;
    token = strtok_r(NULL, delim, &saveptr);
  }

  output[i] = NULL;

  return;
}
