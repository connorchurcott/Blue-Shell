#include "internal.h"
#include "helpers.h"

char prevDirectory[200];

int argumentCount(char *array[]) {

  if (array[0] == NULL) {
    return 0;
  }

  int i = 0;
  while (array[i] != NULL) {
    i++;
  }
  return i;
}

void exitInt(int argCount) {
  if (argCount == 1) {
    exit(0);
  } else {
    char *exitError = FORMAT_MSG("exit", TMA_MSG);
    write(2, exitError, strlen(exitError));
  }
  return;
}

void pwdInt(int argCount) {
  if (argCount == 1) {
    char pwdBuffer[200];
    char *filepath = getcwd(pwdBuffer, sizeof(pwdBuffer));

    if (filepath == NULL) {
      char *cwdError = FORMAT_MSG("pwd", GETCWD_ERROR_MSG);
      write(2, cwdError, strlen(cwdError));
    } else {
      filepath[strlen(filepath)] = '\n';
      filepath[strlen(filepath) + 1] = '\0';
      write(1, filepath, strlen(filepath));
    }

  } else {
    char *pwdError = FORMAT_MSG("pwd", TMA_MSG);
    write(2, pwdError, strlen(pwdError));
  }
  return;
}

void chdirError() {
  char *chdirError = FORMAT_MSG("cd", CHDIR_ERROR_MSG);
  write(2, chdirError, strlen(chdirError));
}

void cdInt(int argCount, char *array[]) {
  // handle too many arguments
  if (argCount > 2) {
    char *cdError = FORMAT_MSG("cd", TMA_MSG);
    write(2, cdError, strlen(cdError));
    return;
  }

  struct passwd *userInfo = getpwuid(getuid());

  // store current directory for future use
  char buffer[200];
  if (getcwd(buffer, sizeof(buffer)) == NULL) {
    char *cwdError = FORMAT_MSG("pwd", GETCWD_ERROR_MSG);
    write(2, cwdError, strlen(cwdError));
  }

  // handle just cd
  if (argCount == 1) {
    chdir(userInfo->pw_dir);
  }

  else if (array[1][0] == '~') {

    char homeBuffer[200];

    // Just ~
    if (strcmp(array[1], "~") == 0) {
      strncpy(homeBuffer, userInfo->pw_dir, sizeof(homeBuffer) - 1);
    }

    // ~/directory_path
    else {
      strncpy(homeBuffer, userInfo->pw_dir, sizeof(homeBuffer) - 1);
      homeBuffer[sizeof(homeBuffer) - 1] = '\0';
      strncat(homeBuffer, array[1] + 1,
              sizeof(homeBuffer) - strlen(homeBuffer) - 1);
    }

    if (chdir(homeBuffer) != 0) {
      chdirError();
    }

  } else if (strcmp(array[1], "-") == 0) {
    if (chdir(prevDirectory) != 0) {
      chdirError();
    }

  } else {
    if (chdir(array[1]) != 0) {
      chdirError();
    }
  }

  strncpy(prevDirectory, buffer, sizeof(prevDirectory));
  return;
}

void helpInt(int argCount, char *array[]) {
  if (argCount > 2) {
    char *helpError = FORMAT_MSG("help", TMA_MSG);
    write(2, helpError, strlen(helpError));
    return;
  }

  char *cdHelp = FORMAT_MSG("cd", CD_HELP_MSG);
  char *pwdHelp = FORMAT_MSG("pwd", PWD_HELP_MSG);
  char *exitHelp = FORMAT_MSG("exit", EXIT_HELP_MSG);
  char *helpHelp = FORMAT_MSG("help", HELP_HELP_MSG);
  char *historyHelp = FORMAT_MSG("history", HISTORY_HELP_MSG);

  if (argCount == 1) {
    write(1, cdHelp, strlen(cdHelp));
    write(1, pwdHelp, strlen(pwdHelp));
    write(1, exitHelp, strlen(exitHelp));
    write(1, helpHelp, strlen(helpHelp));
    write(1, historyHelp, strlen(historyHelp));
    return;
  }

  if (strcmp(array[1], "cd") == 0) {
    write(1, cdHelp, strlen(cdHelp));
  } else if (strcmp(array[1], "pwd") == 0) {
    write(1, pwdHelp, strlen(pwdHelp));
  } else if (strcmp(array[1], "exit") == 0) {
    write(1, exitHelp, strlen(exitHelp));
  } else if (strcmp(array[1], "help") == 0) {
    write(1, helpHelp, strlen(helpHelp));
  } else if (strcmp(array[1], "history") == 0) {
    write(1, historyHelp, strlen(historyHelp));
  } else {
    char *message = createMessage(array[1], EXTERN_HELP_MSG);
    writeOut(1, message, strlen(message));
  }

  return;
}
