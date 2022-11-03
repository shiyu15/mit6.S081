#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(2, "a time argument missing\n");
        exit(1);
    }
    else if (argc > 2)
    {
        fprintf(2, "too many arguments\n");
        exit(1);
    }
    int t = atoi(argv[1]);
    sleep(t);

    exit(0);
}