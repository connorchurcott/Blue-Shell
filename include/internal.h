#include "msgs.h"
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int argumentCount(char *array[]);
void exitInt(int argCount);
void pwdInt(int argCount);
void cdInt(int argCount, char *array[]);
void helpInt(int argCount, char *array[]);
