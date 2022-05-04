#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n;
    scanf("%d", &n);
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("%d,", n);
        while (n > 1)
        {
            if (n % 2)
                n = (3 * n) + 1;
            else
                n = n / 2;
            printf("%d", n);
            if (n != 1)
                printf(",");
            else
                printf(".");
        }
    }
    else
        waitpid(pid, NULL, 0);
    return 0;
}