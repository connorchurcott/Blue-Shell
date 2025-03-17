#include "msgs.h"
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void zombieCleanup();
int lastIndex(char *array[]);
int checkEmptyArray(char *array[]);
void execute(char *input[]);
