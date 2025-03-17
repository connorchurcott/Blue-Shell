#ifndef COMMANDS_H
#define COMMANDS_H

#include "execute.h"
#include "helpers.h"
#include "history.h"
#include "internal.h"
#include "msgs.h"
#include <ctype.h>

void commands(char *array[], int argCount, char *history[], int *historyCur,
              int *historyAll);
void commandList(char *array[], int argCount, char *history[], int *historyCur);

#endif
