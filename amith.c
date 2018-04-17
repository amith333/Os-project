#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
int main()
{
    int a[2];
    int b[2];
    char input_str[100],ch;
    pid_t p;
    if (pipe(a)==-1)
    {
        fprintf(stderr, "Pipe failed" );
        return 1;
    }
    if (pipe(b)==-1)
    {
        fprintf(stderr, "Pipe failed" );
        return 1;
    }
    printf("PLEASE ENTER STRING\n");
    scanf("%[^\n]",input_str);
    p = fork();
 
    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
 
    else if (p > 0)
    {
        char modified_str[100];
        close(a[0]);
        write(a[1], input_str, strlen(input_str)+1);
        close(a[1]);
        wait(NULL);
        close(b[1]);
        read(b[0], modified_str, 100);
        printf("Converted  string is : %s\n", modified_str);
        close(b[0]);
    }
    else
    {
        close(a[1]);
        char modified_str[100];
        read(a[0], modified_str, 100);
        int k = strlen(modified_str);
        int i;
        for (i=0; i<strlen(input_str); i++)
        {
        	ch = input_str[i];
            if (ch >= 'A' && ch <= 'Z')
            input_str[i] = input_str[i] + 32;
            else if (ch >= 'a' && ch <= 'z')
            input_str[i] = input_str[i] - 32;
		}
		strcpy( modified_str,input_str);
        close(a[0]);
        close(b[0]);
        write(b[1], modified_str, strlen(modified_str)+1);
        close(b[1]);
        exit(0);
    }
}
