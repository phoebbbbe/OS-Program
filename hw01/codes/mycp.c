#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("should input: ./mycp srcfile decfile\n");
        exit(0);
    }
    struct stat _stat;
    stat(argv[1], &_stat);
    if (!S_ISREG(_stat.st_mode))
    {
        printf("not a regular file!\n");
        exit(0);
    }
    stat(argv[2], &_stat);
    char decfile[1024] = {0};
    strcpy(decfile, argv[2]);
    if (S_ISDIR(_stat.st_mode))
    {
        char file_name[64] = {0};
        strcpy(file_name, argv[1]);
        char *tmp = strchr(argv[1], '/');
        while (tmp != NULL)
        {
            strcpy(file_name, tmp);
            tmp = strchr(tmp, '/');
        }
        int last_char = strlen(decfile);
        if (decfile[last_char - 1] != '/')
        {
            decfile[last_char - 1] = '/';
            decfile[last_char] = '\0';
        }
        strcat(decfile, file_name);
        printf("%s\n", decfile);
    }
    int fdread = open(argv[1], O_RDONLY);
    assert(fdread != -1);
    int fdwrite = open(decfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    assert(fdwrite != -1);
    char cachestr[128] = {0};
    int current_size = 1;
    while (current_size != 0)
    {
        current_size = read(fdread, cachestr, 128);
        write(fdwrite, cachestr, current_size);
    }
    close(fdread);
    close(fdwrite);
    exit(0);
}