#define _POSIX_C_SOURCE 1
#include "commands.h"
#include "cwdWrite.h"
#include "execute.h"
#include "handleSig.h"
#include "history.h"
#include "input.h"
#include "internal.h"

char *history[10];
int historyAllCount = 0;
int historyCurCount = 0;

int main() {

  struct sigaction handler;
  handler.sa_handler = handleSigint;
  handler.sa_flags = 0;
  sigemptyset(&handler.sa_mask);
  sigaction(SIGINT, &handler, NULL);

  while (1) {
    char inputBuffer[INPUT_BUFFER_SIZE];
    char *tokenOutput[INPUT_BUFFER_SIZE];

    writeCWD();
    getInput(inputBuffer, INPUT_BUFFER_SIZE);

    if (errno == EINTR) {
      errno = 0;
      continue;
    }

    tokenizeInput(inputBuffer, tokenOutput);

    int argCount = argumentCount(tokenOutput);
    commands(tokenOutput, argCount, history, &historyCurCount,
             &historyAllCount);
  }
}
