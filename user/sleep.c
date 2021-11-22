#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int new;
  if (argc <= 1)
  {
    fprintf(2, "usage: sleep NUMBER\n");
    exit(1);
  }
  new = atoi(argv[1]);
  sleep(new);
  exit(0);
}
