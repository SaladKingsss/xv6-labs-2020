#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
        char buf;
        int p[2];
        int pid;
        pipe(p);        //create a pipe

        //child process
        if (fork() == 0)
        {
                pid = getpid();

                //if read a byte from parent process
                read(p[0], &buf, 1);
                close(p[0]);

                printf("%d: received ping\n", pid);

                //write the byte on the pipe to the parent
                write(p[1], "0", 1);
                close(p[1]);
        }

        //parent process
        else
        {
                pid = getpid();

                //send a byte to the child
                write(p[1], "0", 1);
                close(p[1]);

                //???
                wait(0);

                //if read the byte from child process
                read(p[0], &buf, 1);
                close(p[0]);

                printf("%d: received pong\n", pid);
        }

        exit(0);
}
