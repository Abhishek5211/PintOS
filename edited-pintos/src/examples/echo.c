#include <stdio.h>
#include <syscall.h>
#include "lib/lib.h"

int
main (int argc, char **argv)
{
  int i;

  for (i = 0; i < argc; i++)
{

    msg ("argc");
    printf ("%s ", argv[i]);
}
  printf ("\n");

  return EXIT_SUCCESS;
}
