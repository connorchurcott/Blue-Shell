#include "helpers.h"

void writeOut(int stream, char *message, int size) {
  int status = write(stream, message, size);
  if (status == -1) {
    if (errno == EINTR) {
      // handle
    }
  }
  return;
}

char *createMessage(char *first, char *second) {
  static char output[300];
  output[0] = '\0';
  strcpy(output, first);
  strcat(output, ": ");
  strcat(output, second);
  strcat(output, "\n");
  return output;
}

char *createHisMessage(char *first, char *second) {
  static char output[300];
  output[0] = '\0';
  strcpy(output, first);
  strcat(output, "\t");
  strcat(output, second);
  return output;
}

char *unTokenCommand(char *array[]) {
  static char output[300];
  output[0] = '\0';

  for (int i = 0; array[i] != NULL; i++) {
    strcat(output, array[i]);

    if (array[i + 1] != NULL) {
      strcat(output, " ");
    }
  }

  strcat(output, "\n");
  return output;
}

char *intToString(int value) {
  static char buf[30];
  sprintf(buf, "%d", value);
  return buf;
}
