#include "handleSig.h"

void handleSigint(int signal) {
  if (signal == SIGINT) {
    char *buf = "\n";
    write(1, buf, strlen(buf));
    helpInt(1, NULL);
    return;
  }
}
