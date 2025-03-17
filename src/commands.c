#include "commands.h"

void commands(char *array[], int argCount, char *history[], int *historyCur,
              int *historyAll) {

  if (checkEmptyArray(array)) {
    return;
  }

  // handle !! and !n
  if (strcmp(array[0], "!!") == 0) {
    executePrevCommand(history, historyCur, historyAll);
    return;
  }

  if (array[0][0] == '!') {
    executeNthCommand(history, array, historyCur, historyAll);
    return;
  }

  // Add to history
  char *command = unTokenCommand(array);
  insertToHistory(history, command, historyCur, historyAll);

  // All valid options for internal commands, else external execute
  if (strcmp(array[0], "exit") == 0) {
    exitInt(argCount);
  } else if (strcmp(array[0], "pwd") == 0) {
    pwdInt(argCount);
  } else if (strcmp(array[0], "cd") == 0) {
    cdInt(argCount, array);
  } else if (strcmp(array[0], "help") == 0) {
    helpInt(argCount, array);
  } else if (strcmp(array[0], "history") == 0) {
    printHistory(history, historyCur);
  }

  else {
    execute(array);
  }

  return;
}

void commandList(char *array[], int argCount, char *history[],
                 int *historyCur) {

  // All valid options for internal commands, else external execute
  if (strcmp(array[0], "exit") == 0) {
    exitInt(argCount);
  } else if (strcmp(array[0], "pwd") == 0) {
    pwdInt(argCount);
  } else if (strcmp(array[0], "cd") == 0) {
    cdInt(argCount, array);
  } else if (strcmp(array[0], "help") == 0) {
    helpInt(argCount, array);
  } else if (strcmp(array[0], "history") == 0) {
    printHistory(history, historyCur);
  }

  else {
    execute(array);
  }
  return;
}
