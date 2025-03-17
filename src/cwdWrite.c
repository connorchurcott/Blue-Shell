#include "cwdWrite.h"

void writeCWD() {
  char cwdBuffer[CWD_BUFFER_SIZE];
  char *cwd = getcwd(cwdBuffer, CWD_BUFFER_SIZE);
  int size = strlen(cwd);

  if (cwd == NULL) {
    const char *errorMsg = FORMAT_MSG("shell", GETCWD_ERROR_MSG);
    write(2, errorMsg, strlen(errorMsg));
  }

  else {
    cwdBuffer[size] = '$';
    cwdBuffer[size + 1] = ' ';
    cwdBuffer[size + 2] = '\0';
    size += 2;
    write(1, cwd, size);
  }

  return;
}
