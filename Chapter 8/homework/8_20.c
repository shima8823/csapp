#include "csapp.h"

int main(int argc, char **argv, char **envp)
{
    execve("/bin/ls", argv, envp);
    exit(0);
}