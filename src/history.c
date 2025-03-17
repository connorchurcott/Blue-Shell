#include "history.h"

void insertToHistory(char *history[], char *command, int *historyCurCount,
                     int *historyAllCount) {

  if (*historyCurCount == 10) {
    free(history[9]);
  } else {
    (*historyCurCount)++;
  }

  for (int i = *historyCurCount - 1; i > 0; i--) {
    history[i] = history[i - 1];
  }

  // Create message to insert
  char *num = intToString(*historyAllCount);
  char *message = createHisMessage(num, command);

  // Allocate memory for new command
  history[0] = malloc((strlen(message) + 1) * sizeof(char));
  if (history[0] != NULL) {
    strcpy(history[0], message);
  }

  (*historyAllCount)++;
  return;
}

void printHistory(char *history[], int *historyCurCount) {
  for (int i = 0; i < *historyCurCount; i++) {
    writeOut(1, history[i], strlen(history[i]));
  }
  return;
}

void executePrevCommand(char *history[], int *historyCurCount,
                        int *historyAllCount) {

  // Handle history empty
  if (*historyCurCount == 0) {
    char *historyError = FORMAT_MSG("history", HISTORY_NO_LAST_MSG);
    writeOut(2, historyError, strlen(historyError));
  }

  // Get previous history item
  char *prevHistoryEntry = history[0];

  // Extract the command out of it, skip the tab character, write it
  char *command = strchr(prevHistoryEntry, '\t');
  command++;
  writeOut(1, command, strlen(command));

  // Retokenize the command
  char *commandTokens[20];
  tokenizeInput(command, commandTokens);
  int commandArgCount = argumentCount(commandTokens);

  commandList(commandTokens, commandArgCount, history, historyCurCount);
  strcat(command, "\n");
  insertToHistory(history, command, historyCurCount, historyAllCount);

  return;
}

void executeNthCommand(char *history[], char *array[], int *historyCurCount,
                       int *historyAllCount) {

  char *historyError = FORMAT_MSG("history", HISTORY_INVALID_MSG);
  char *command = array[0];
  char *nStr = &command[1];

  // check if after ! is a digit
  for (int i = 0; nStr[i] != '\0'; i++) {
    if (!isdigit(nStr[i])) {
      writeOut(2, historyError, strlen(historyError));
      return;
    }
  }

  int n = atoi(nStr);

  // check valid history item
  if (n > *historyAllCount || n < 0) {
    writeOut(2, historyError, strlen(historyError));
    return;
  }

  int index = *historyAllCount - n - 1;

  // format the command from history
  char *historyEntry = history[index];
  char *historyCommand = strchr(historyEntry, '\t');
  historyCommand++;
  write(1, historyCommand, strlen(historyCommand));

  // tokenize and run
  char *commandTokens[20];
  tokenizeInput(historyCommand, commandTokens);
  int commandArgCount = argumentCount(commandTokens);
  commandList(commandTokens, commandArgCount, history, historyCurCount);
  strcat(historyCommand, "\n");
  insertToHistory(history, historyCommand, historyCurCount, historyAllCount);

  return;
}
