#include "execute.h"
#include <stdio.h>

void zombieClean() {
  int cleanWStatus;
  pid_t childPID;

  childPID = waitpid(-1, &cleanWStatus, WNOHANG);
  while (childPID > 0) {
    if (!WIFEXITED(cleanWStatus)) {
      char *waitZombieError = FORMAT_MSG("shell", WAIT_ERROR_MSG);
      write(2, waitZombieError, strlen(waitZombieError));
    }

    childPID = waitpid(-1, &cleanWStatus, WNOHANG);
  }
  return;
}

int lastIndex(char *array[]) {
  int i = 0;

  if (array[i] == NULL) {
    return i;
  }

  while (array[i] != NULL) {
    i++;
  }
  return i - 1;
}

int checkEmptyArray(char *array[]) {
  if (array[0] == NULL || strcmp(array[0], "") == 0) {
    char *execError = FORMAT_MSG("shell", EXEC_ERROR_MSG);
    write(2, execError, strlen(execError));
    return 1;
  }
  return 0;
}

void execute(char *input[]) {
  if (checkEmptyArray(input)) {
    return;
  }

  // Determine if background and remove & from array
  int background = 0;
  int finalIndex = lastIndex(input);

  if (strcmp(input[finalIndex], "&") == 0) {
    background = 1;
    input[finalIndex] = NULL;
    if (checkEmptyArray(input)) {
      return;
    }
  }

  pid_t pid = fork();

  // Handle error
  if (pid < 0) {
    char *forkError = FORMAT_MSG("shell", FORK_ERROR_MSG);
    write(2, forkError, strlen(forkError));
  }

  // Is child
  else if (pid == 0) {

    execvp(input[0], input);
    char *execError = FORMAT_MSG("shell", EXEC_ERROR_MSG);
    write(2, execError, strlen(execError));
  }

  // Is parent
  else {
    int wstatus;

    // Is background
    if (background) {
      // dont really do anything
    }

    // Is foreground
    else {
      waitpid(pid, &wstatus, 0);
      if (!WIFEXITED(wstatus)) {
        char *waitError = FORMAT_MSG("shell", WAIT_ERROR_MSG);
        write(2, waitError, strlen(waitError));
      }
    }
  }

  zombieClean();
  return;
}
