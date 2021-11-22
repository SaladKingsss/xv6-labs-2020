#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PRIME_NUMBER 35
#define END_OF_READ 0
#define END_OF_WRITE 1

//this is what child process need to do:
void child(int *pl)
{
        int pe[2];
        int read_result;
        int num;

        //judge if the read process has reach the end
        close(pl[END_OF_WRITE]);

        //read the first number (where to put these number?)
        read_result = read(pl[END_OF_READ], &num, sizeof(int));
        if (read_result == 0)
                exit(0);

        pipe(pe);

        if (fork() == 0) //child process
        {
                child(pe);
        }
        else //parent process,which means this process
        {
                close(pe[END_OF_READ]);
                printf("prime %d\n", num);
                int prime = num;

                   //here is extremly important : do not mixed pl with pe 
                while (read(pl[END_OF_READ], &num, sizeof(int)) != 0)
                {
                        if ((num % prime) != 0)
                        {
                                //send a number to the child process
                                write(pe[END_OF_WRITE], &num, sizeof(int));
                        }
                }
                close(pe[END_OF_WRITE]);

                wait((int *) 0);

                exit(0);
        }
}

int main(int argc, char *argv[])
{
        int p[2];
        pipe(p); //create a pipe

        //child process
        if (fork() == 0)
        {
                //here maybe occured a loop of process creation(yes! that's it)
                child(p);
        }

        //parent process
        else
        {
                close(p[END_OF_READ]);
                for (int i = 2; i <= MAX_PRIME_NUMBER; i++)
                {
                        write(p[END_OF_WRITE], &i, sizeof(int));
                }
                close(p[END_OF_WRITE]);
                wait((int *) 0);
        }
        exit(0);
}
