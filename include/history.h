#ifndef HISTORY_H
#define HISTORY_H

#include "commands.h"
#include "helpers.h"
#include "input.h"
#include "internal.h"
#include "msgs.h"
#include <string.h>

void insertToHistory(char *history[], char *command, int *historyCurCount,
                     int *historyAllCount);
void printHistory(char *history[], int *historyCurCount);
void executePrevCommand(char *history[], int *historyCurCount,
                        int *historyAllCount);
void executeNthCommand(char *history[], char *array[], int *historyCurCount,
                       int *historyAllCount);

#endif
