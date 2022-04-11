#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
extern char **environ;

int start(char *command[]);
void ret_msg(pid_t pid, int ret_code);
int run(char *command[]);
int shell_kill(char *command[]);
int shell_stop(char *command[]);
int shell_continue(char *command[]);

int main()
{
  int n;
  char *token[100];
  char palavra[100] = "";
  while (1)
  {
    printf("myshell>");
    fflush(stdout);
    if (fgets(palavra, 100, stdin) == NULL) {
      return 0;
    }
    token[0] = strtok(palavra, " \t\n");
    if (token[0] != NULL) {
      n = 0;
      while (token[n] != 0)
      {
        n++;
        token[n] = strtok(NULL, " \t\n");
        if (token[n] == NULL)
        {
          /*if (n == 2)
          { // Precisei colocar isso por que se o argv no execvp for direto null ele da erro.
            token[n] = "";
            n++;
          }*/
          token[n] = 0;
          break;
        }
      }
      /*for (int i = 0; i <= n; i++) // Print do comando para debug
      {
        printf("%s ", token[i]);
      }*/
      printf("\n");
      if (strcmp(token[0], "start") == 0) {
        start(token+1);
      }
      else if (strcmp(token[0], "wait") == 0)
      {
        int wstatus;
        pid_t wait_code = wait(&wstatus); // @todo Verificar como essa função se comporta, pois parece que ela não é bloqueante nesse nível aqui
        if (wait_code == -1) {
          printf("myshell: não há processos restantes\n");
        } else if ( WIFEXITED(wstatus)) {
          printf("myshell: processo %d terminou normalmente\n", wait_code);
        } else if ( WIFSIGNALED(wstatus)) {
          printf("myshell: processo %d terminou de forma anormal com sinal %d\n", wait_code, WTERMSIG(wstatus));
        }
        
      }
      else if (strcmp(token[0], "run") == 0)
      {
        run(token+1);
      }
      else if (strcmp(token[0], "kill") == 0)
      {
        shell_kill(token+1);
      }
      else if (strcmp(token[0], "stop") == 0)
      {
        shell_stop(token+1);
      }
      else if (strcmp(token[0], "continue") == 0)
      {
        shell_continue(token+1);
      }
      else if (strcmp(token[0], "pid") == 0) // Só pra facilitar
      {
        printf("pid %d\n", getpid());
        /*printf("token %d\n", token);
        printf("token+1 %d\n", token+1);
        printf("token[1] %d\n", token[1]);*/
      }
      else if (strcmp(token[0], "exit") == 0)
      {
        printf("Closing myshell\n");
        return 0;
      }
      else
      {
        printf("myshell: comando desconhecido: %s\n", token[0]);
      }
    }
  }
}

int start(char *command[]) {
  if (command[0] != NULL) {
    pid_t pid;
    pid = fork();
    if (pid == 0) {      
      int ret_code = execvp(command[0], command);
      pid = getpid();
      ret_msg(pid, ret_code);
      exit(ret_code);
    }
    else
    {
      printf("myshell: processo %d iniciado\n", pid);
      return 0;
    }
  }
  return -1;
}

int run(char *command[]) {
  if (command[0] != NULL) {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
      int ret_code = execvp(command[0], command);
      pid = getpid();
      ret_msg(pid, ret_code);
      exit(ret_code);
    }
    else
    {
      printf("myshell: processo %d iniciado\n", pid);
      wait(NULL);
      return 0;
    }
  }
  return -1;
}

int shell_kill(char *command[]) {
  if (command[0] != NULL) {
    int pid = atoi(*(command));
    if (kill(pid, SIGKILL) == 0) {
      printf("myshell: processo %d foi finalizado\n", pid);
    } else {
      printf("myshell: processo %d não pôde ser finalizado\n", pid);
    }
  } else {
    printf("myshell: argumento esperado\n");
    
  }
  return -1;

}

int shell_stop(char *command[]) {
  if (command[0] != NULL) {
    int pid = atoi(*(command));
    if (kill(pid, SIGSTOP) == 0) {
      printf("myshell: processo %d parou a execução\n", pid);
    } else {
      printf("myshell: processo %d não pôde ser parado\n", pid);
    }
  } else {
    printf("myshell: argumento esperado\n");
    
  }
  return -1;
}

int shell_continue(char *command[]) {
  if (command[0] != NULL) {
    int pid = atoi(*(command));
    if (kill(pid, SIGCONT) == 0) {
      printf("myshell: processo %d voltou a execução\n", pid);
    } else {
      printf("myshell: processo %d não pôde ser reativado\n", pid);
    }
  } else {
    printf("myshell: argumento esperado\n");
    
  }
  return -1;
}

void ret_msg(pid_t pid, int ret_code) {
  if (ret_code == 0) {
    printf("myshell: processo %d finalizou normalmente com status 0\n", pid);
  } else {
    printf("myshell: processo %d finalizou com status desconhecido: %d \n", pid, ret_code);
  }
}