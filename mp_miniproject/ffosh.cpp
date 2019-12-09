#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "function.h"
#include "shell.h"
using namespace std;

int main(void) {
  std::map<string, string> main_map;
  while (1) {
    pid_t child_pid, wait_pid;
    int wstatus;

    setpath();
    printprompt();

    //parse input, get command, search comand, handle incorrect command

    shell myshell;
    myshell.variable_map = main_map;
    myshell.initial();
    //myshell.printcommand();
    if (myshell.exit_flag == 1) {
      //printf("shell  prepare to exit\n");
      break;
    }
    if (myshell.no_fork_flag == 1) {
      main_map = myshell.variable_map;
      continue;
    }
    child_pid = fork();
    if (child_pid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }

    //parse input & handle input errors

    if (child_pid == 0) {
      // printf("Child PID is %ld\n", (long)getpid());
      myshell.execute();
      perror("execve");
      exit(EXIT_FAILURE);
    }
    else {
      wait_pid = waitpid(child_pid, &wstatus, WUNTRACED | WCONTINUED);

      if (wait_pid == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }
      if (myshell.buildin_flag == 0) {
        if (WEXITSTATUS(wstatus) == 0) {
          printf("Program was successful\n");
        }
      }
      if (WEXITSTATUS(wstatus) != 0) {
        printf("Program failed with code %d\n", WEXITSTATUS(wstatus));
      }
      else if (WIFSIGNALED(wstatus)) {
        printf("Terminated by signal %d\n", WTERMSIG(wstatus));
      }
    }
  }
  return EXIT_SUCCESS;
}
