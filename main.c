#include <string.h>
#include <stdio.h>

int main()
{
    char palavra[100];
    char *palavra1;
    printf("myshell>");
    fflush(stdout);
    fgets(palavra, 100, stdin);
    char* token;
    token = strtok(palavra, " \t\n");
    while (token != NULL) {
        printf("%s \r\n", token);
        
        token = strtok(NULL, " \t\n");
    }
    return 0;
}
