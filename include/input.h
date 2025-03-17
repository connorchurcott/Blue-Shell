#include "msgs.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define INPUT_BUFFER_SIZE 200
void getInput(char *inputBuffer, int size);
void tokenizeInput(char *input, char *output[]);
