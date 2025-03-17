#include "msgs.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void writeOut(int stream, char *message, int size);
char *createMessage(char *first, char *second);
char *createHisMessage(char *first, char *second);
char *unTokenCommand(char *array[]);
char *intToString(int value);
